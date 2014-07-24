// Disable "Missing XML comment for public type or member" warning.
// This file contains only code being accessed through an abstract interface class.
// The public methods are documented in this abstract interface class.
#pragma warning disable 1591

using System;
using System.Collections.Generic;
using System.Text;
using Nokia.Iowarrior;
using System.Threading;

namespace Nokia.Iowarrior.Cards
{
    public sealed class IowCardTouchRC_V2 : IowCard
    {
        #region Parameter bits definition

        class CardCommand : IowCardCommand
        {
            public CardCommand(String command)
                : base(command)
            {
                CommandMap["screen:width=###"] = "w";
                CommandMap["screen:height=###"] = "h";
                CommandMap["touch:level=###"] = "l";
                CommandMap["touch:release"] = "0";
                CommandMap["touch:full"] = "255";
                CommandMap["move:pos=###/###"] = "xy";
                CommandMap["move:line=###/###/###/###/###"] = "x1/y1/x2/y2/speed";
            }
        }
        #endregion

        Int32 screenWidth;
        Int32 screenHeight;
        Int32 touchLevel;
        Int32 posX = -1;
        Int32 posY = -1;
        Int32 lineX1 = -1;
        Int32 lineY1 = -1;
        Int32 lineX2 = -1;
        Int32 lineY2 = -1;
        Int32 lineSpeed = -1;

        public IowCardTouchRC_V2()
            : base()
        {
        }

        public IowCardTouchRC_V2(IowDevice iowDevice, Int32 index, IowCardInformation iowCardInformation)
            : base(iowDevice, index, iowCardInformation)
        {
            Reset();
        }

        public override void Shutdown()
        {
            // Do all required to get card in safe state.
        }

        public override void Reset()
        {
            IowDevice.WriteOutput(25, true);         // Release touch
            IowDevice.WriteOutput(24, true);         // Enable RDAC

            // needed to solve startup problems
            IowDevice.EnableSpi();
            WriteResistor((Byte)145, (Byte)85, (Byte)145, (Byte)85);
            IowDevice.DisableSpi();

            Thread.Sleep(100);
            IowDevice.EnableSpi();
        }

        public override ICollection<String> KnownCommands
        {
            get { return new CardCommand("").KnownCommands; }
        }

        public override IowCardCommand CheckCommand(String command)
        {
            CardCommand cc = new CardCommand(command);

            if (cc.HasIndex && (cc.IndexValue != Index))
                return cc;

            if (cc.HasName && (cc.NameValue != CardName))
                return cc;

            cc.IsExecutable = true;

            switch (cc.Command)
            {
                case "screen":
                    foreach (String fieldName in cc.FieldNames)
                    {
                        String fieldValue = cc.GetFieldValue(fieldName);

                        switch (fieldName)
                        {
                            case "width":
                                cc.IsExecutable = cc.IsExecutable && Int32.TryParse(fieldValue, out screenWidth);
                                break;
                            case "height":
                                cc.IsExecutable = cc.IsExecutable && Int32.TryParse(fieldValue, out screenHeight);
                                break;
                            default:
                                cc.IsExecutable = false;
                                return cc;
                        }
                    }
                    break;
                case "touch":
                    foreach (String fieldName in cc.FieldNames)
                    {
                        switch (fieldName)
                        {
                            case "level":
                                cc.IsExecutable = cc.IsExecutable && Int32.TryParse(cc.GetFieldValue(fieldName), out touchLevel);
                                if (touchLevel >= 0 && touchLevel < 256)
                                    cc.IsExecutable = true;
                                else
                                    cc.IsExecutable = false;
                                break;
                            case "release":
                                touchLevel = 0;
                                break;
                            case "full":
                                touchLevel = 255;
                                break;
                            default:
                                cc.IsExecutable = false;
                                break;
                        }
                    }
                    break;
                case "move":
                    foreach (String fieldName in cc.FieldNames)
                    {
                        String fieldValue = cc.GetFieldValue(fieldName);

                        switch (fieldName)
                        {
                            case "pos":
                                String[] pos = fieldValue.Split("/".ToCharArray());
                                cc.IsExecutable = cc.IsExecutable && (pos.Length >= 2);
                                if (cc.IsExecutable)
                                {
                                    cc.IsExecutable = cc.IsExecutable && Int32.TryParse(pos[0], out posX);
                                    cc.IsExecutable = cc.IsExecutable && Int32.TryParse(pos[1], out posY);
                                    if (posX >= 0 && posX < screenWidth && posY >= 0 && posY <= screenHeight)
                                        cc.IsExecutable = true;
                                    else
                                        cc.IsExecutable = false;
                                }
                                break;
                            case "line":
                                String[] param = fieldValue.Split("/".ToCharArray());
                                cc.IsExecutable = cc.IsExecutable && (param.Length >= 5);
                                if (cc.IsExecutable)
                                {
                                    Int32.TryParse(param[0], out lineX1);
                                    Int32.TryParse(param[1], out lineY1);
                                    Int32.TryParse(param[2], out lineX2);
                                    Int32.TryParse(param[3], out lineY2);
                                    Int32.TryParse(param[4], out lineSpeed);
                                    if (lineX1 >= 0 && lineX1 < screenWidth && lineX2 >= 0 && lineX2 < screenWidth
                                        && lineY1 >= 0 && lineY1 < screenHeight && lineY2 >= 0 && lineY2 < screenHeight
                                        && lineSpeed > 0 && lineSpeed < 10000)
                                    {
                                        cc.IsExecutable = true;
                                    }
                                    else
                                    {
                                        cc.IsExecutable = false;
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                default:
                    cc.IsExecutable = false;
                    break;
            }
            return cc;
        }

        public override IowCardCommand ExecuteCommand(String command)
        {
            IowCardCommand cc = CheckCommand(command);
            cc.ExecutionSuccess = false;

            if (cc.IsExecutable)
            {
                switch (cc.Command)
                {
                    case "screen":
                        cc.ExecutionSuccess = true;
                        break;
                    case "touch":
                        cc.ExecutionSuccess = TryTouch();
                        break;
                    case "move":
                        foreach (String fieldName in cc.FieldNames)
                        {
                            switch (fieldName)
                            {
                                case "pos":
                                    cc.ExecutionSuccess = TryTouch();
                                    break;
                                case "line":
                                    cc.ExecutionSuccess = TryLine();
                                    break;
                            }
                        }
                        break;
                }
            }

            return cc;
        }

        private Boolean TryLine()
        {
            // Check line parameters
            if (lineX1 < 0 || lineY1 < 0 || lineX2 < 0 || lineY2 < 0 || lineSpeed <= 0)
                return false;

            if (lineX1 >= screenWidth || lineY1 >= screenHeight || lineX2 >= screenWidth || lineY2 >= screenHeight || lineSpeed > 10000)
                return false;

            // Calculate distances between origin and destination
            Int32 distX = lineX2 - lineX1;
            Int32 distY = lineY2 - lineY1;
            Int32 distSquare = distX * distX + distY * distY;

            // totalTime is the complete time [ms] the drawing operation shall take (lineSpeed is given in pixels/sec)
            Double totalTime = 1000 * Math.Sqrt(distSquare) / lineSpeed;

            // Approximately calculate the number of steps
            Double correctionFactor = 0.065;     // Factor was derived from measurements on development machine [WXP_SP2 on Lenovo T60p]
            Int32 nrOfSteps = (Int32)(correctionFactor * totalTime / IowDevice.MinimumTimeBetweenAccesses);

            // Origin and destination are the same => Single point
            if (distX == 0 && distY == 0)
            {
                return TryTouch(lineX1, lineY1);
            }

            // Calculate step width in each direction

            Double stepX;
            Double stepY;

            if (nrOfSteps == 0)
            {
                nrOfSteps = 1;      // Time and speed settings result in less than one step:
                stepX = distX;      // Draw at least the start and the end point of the line.
                stepY = distY;
            }
            else
            {
                stepX = 1.0 * distX / nrOfSteps;    // Several steps: calculate slope in each direction
                stepY = 1.0 * distY / nrOfSteps;
            }

            // Draw the line as a sequence of single touch events

            Double x = lineX1;
            Double y = lineY1;

            while (nrOfSteps >= 0)
            {
                TryTouch((int)x, (int)y);
                x += stepX;
                y += stepY;
                nrOfSteps--;
            }

            return true;
        }

        private Boolean TryTouch()
        {
            return TryTouch(posX, posY);
        }

        private Boolean TryTouch(int posX, int posY)
        {
            if (touchLevel == 0)
            {
                IowDevice.WriteOutput(25, true);  // release
                return true;
            }

            if (posX < 0 || posX >= screenWidth)
                return false;

            if (posY < 0 || posY >= screenHeight)
                return false;

            TouchScreen(posX, posY);

            return true;
        }

        private void TouchScreen(int posX, int posY)
        {
            int DAC_RANGE = 255;
            double m_fXYRatio = 1.0;
            double m_fAX = 0.0;
            double m_fBX = 1.0;
            double m_fAY = 0.0;
            double m_fBY = 1.0;

            int nXCorrection = (int)(m_fAX + m_fBX * posX);
            int nYCorrection = (int)(m_fAY + m_fBY * posY);

            int nWiperPosX = nXCorrection * DAC_RANGE / screenWidth;
            int nWiperPosY = nYCorrection * DAC_RANGE / screenHeight;
            int nWiperPosZ = touchLevel;

            int nWiperPosY1, nWiperPosY2;	//Uses two potentiometers to simulate Y panel
            nWiperPosY1 = (int)(nWiperPosY / m_fXYRatio);
            nWiperPosY2 = (int)((DAC_RANGE - DAC_RANGE / m_fXYRatio) + nWiperPosY1);

            IowDevice.WriteOutput(24, true);               // Enable RDAC          

            WriteResistor((Byte)nWiperPosX, (Byte)nWiperPosY2, (Byte)nWiperPosZ, (Byte)nWiperPosY1);

            IowDevice.WriteOutput(25, false);              // touch!
        }        

        private void WriteResistor(Byte resistor1, Byte resistor2, Byte resistor3, Byte resistor4)
        {
            Int64 bits = 0;
            bits = bits << 2;
            bits = bits | 3;                    // selection bit resistor4 
            bits = bits << 8;
            bits = bits | resistor4;            // data resistor4
            bits = bits << 2;
            bits = bits | 2;                    // selection bit resistor3 
            bits = bits << 8;
            bits = bits | resistor3;            // data resistor3
            bits = bits << 2;
            bits = bits | 1;                    // selection bit resistor2    
            bits = bits << 8;
            bits = bits | resistor2;            // data resistor2
            bits = bits << 2;
            bits = bits | 0;                    // selection bit resistor1     
            bits = bits << 8;
            bits = bits | resistor1;            // data resistor1

            Byte[] intBytes = BitConverter.GetBytes(bits); 
            // Byte Reihenfolge drehen. Höherwertigstes Byte muss zuerst gesendet werden
            Byte[] commandBytes = { intBytes[4], intBytes[3], intBytes[2], intBytes[1], intBytes[0] };

            if (!IowDevice.IsInSpecialModeSpi)
                IowDevice.EnableSpi();

            IowDevice.WriteSpiBytes(commandBytes);
        }
    }
}