using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;

namespace Nokia.Tea.CommonFramework.Rcms.TouchControllerCY
{
    internal class CyMessageData
    {
        private CyFingersState currentCyFingersState;
        private int defaultSpeed = 80;
        private string displayOrientation;
        private int numberOfFingers;
        private int screenHeight;
        private int screenWidth;
        private double stepX;
        private double stepY;
        private int timeBetweenSteps;
        private double xMax;
        private double xMin;
        private double yMax;
        private double yMin;
        private List<byte> zList;
        private int lastX;
        private int lastY;
        private string hwRevision;

        public CyMessageData(int numberOfFingers, int screenWidth, int screenHeight, string displayOrientation, int timeBetweenSteps, int xMax, int xMin, int yMax, int yMin, List<byte> zList, string hwRevision)
        {
            this.numberOfFingers = numberOfFingers;
            this.screenWidth = screenWidth;
            this.screenHeight = screenHeight;
            this.displayOrientation = displayOrientation.ToLower();
            this.timeBetweenSteps = timeBetweenSteps;
            this.xMax = xMax >> 6;
            this.xMin = xMin >> 6;
            this.yMax = yMax >> 6;
            this.yMin = yMin >> 6;
            this.stepX = (this.xMax - this.xMin) / ((double) screenWidth);
            this.stepY = (this.yMax - this.yMin) / ((double) screenHeight);
            this.zList = zList;
            this.hwRevision = hwRevision;

            string traceMessage = "Number of fingers: " + numberOfFingers + Environment.NewLine + "ScreenHeight: " + screenHeight + Environment.NewLine + "ScreenWidth: " + screenWidth;
#if TRACE_LOG
            BlackBox.Log(traceMessage);
#endif
            Console.WriteLine(traceMessage);

            string format = "z Bytes: {0}, {1}, {2}, {3}";
            object[] args = new object[4];
            object[] objArray2 = args;
            int index = 0;
            objArray2[index] = zList[0].ToString("X");
            object[] objArray3 = args;
            int num3 = 1;
            objArray3[num3] = zList[1].ToString("X");
            object[] objArray4 = args;
            int num4 = 2;
            objArray4[num4] = zList[2].ToString("X");
            object[] objArray5 = args;
            int num5 = 3;
            objArray5[num5] = zList[3].ToString("X");
            Console.WriteLine(string.Format(format, args));
            this.currentCyFingersState = new CyFingersState(numberOfFingers);
            this.lastX = -1;
            this.lastY = -1;
        }

        public bool AllFingrsReleased()
        {
            return (!this.currentCyFingersState.GetFingerState(1).FingerPressed && !this.currentCyFingersState.GetFingerState(2).FingerPressed);
        }

        private CyFingerPathData CalculateFingerPath(object[] marbleTouchData, int finger)
        {
            //List<FingerState> list = new List<FingerState>();
            //foreach (MarbleTouchData touchData in marbleTouchData)
            //{
            //    // If lenght of touch press is longer than time between steps, calculate the steps needes.
            //    int moveLength = int.Parse(touchData.Wait);
            //    if (moveLength > timeBetweenSteps)
            //    {
            //        int steps = moveLength / timeBetweenSteps;
            //        for (int i = 0; i < steps; i++)
            //        {
            //            Vector coordinates = new Vector(double.Parse(touchData.X), double.Parse(touchData.Y));
            //            Vector vectorRaw = this.CalculateRawCoordinates(coordinates);
            //            FingerState state = new FingerState(vectorRaw, true);
            //            list.Add(state);
            //        }
            //    }
            //    else
            //    {
            //        Vector coordinates = new Vector(double.Parse(touchData.X), double.Parse(touchData.Y));
            //        Vector vectorRaw = this.CalculateRawCoordinates(coordinates);
            //        FingerState state = new FingerState(vectorRaw, true);
            //        list.Add(state);
            //    }
            //}

            CyFingerPathData fingerPathData = new CyFingerPathData();
            //fingerPathData.Data = list;
            return fingerPathData;
        }

        public List<byte[]> CalculateMessages(object[] marbleTouchData)
        {
            //string[] strArray;
            int num;
            //if (parameters.Contains(";"))
            //{
            //    strArray = parameters.Split(new char[] { ';' });
            //}
            //else
            //{
            //    strArray = new string[] { parameters };
            //}
            List<CyFingerPathData> list = new List<CyFingerPathData>();
            for (num = 0; num < this.numberOfFingers; num++)
            {
                list.Add(new CyFingerPathData());
            }
            // No multifinger support yet. Needs two dimensional array. Or list of arrays. marbleTouchData list
            list[0] = this.CalculateFingerPath(marbleTouchData, 1);
            //for (int i = 0; i < strArray.Count<string>(); i++)
            //{
            //    string str = strArray[i].ToLower();
            //    if (!(str == ""))
            //    {
            //        list[i] = this.CalculateFingerPath(str, i + 1);
            //    }
            //}
            int length = 0;
            for (num = 0; num < this.numberOfFingers; num++)
            {
                if (list[num].Length > length)
                {
                    length = list[num].Length;
                }
                if (list[num].Length == 0)
                {
                    list[num].Data.Add(this.currentCyFingersState.GetFingerState(num + 1));
                }
            }
            FingerState state = null;
            FingerState state2 = null;
            List<byte[]> list2 = new List<byte[]>();
            for (int j = 0; j < length; j++)
            {
                if (j < list[0].Length)
                {
                    state = list[0].Data[j];
                }
                else
                {
                    state = list[0].Data.Last<FingerState>();
                }
                if (j < list[1].Length)
                {
                    state2 = list[1].Data[j];
                }
                else
                {
                    state2 = list[1].Data.Last<FingerState>();
                }
                list2.Add(this.CalculateCyMessage(state, state2));
            }
            if (length > 0)
            {
                state = list[0].Data.Last<FingerState>();
                state2 = list[1].Data.Last<FingerState>();
                if (!list[0].IsLastCommandHold)
                {
                    state.FingerPressed = false;
                }
                if (!list[1].IsLastCommandHold)
                {
                    state2.FingerPressed = false;
                }
                this.currentCyFingersState.AddFinger(state, 1);
                this.currentCyFingersState.AddFinger(state2, 2);
            }
            return list2;
        }

        private byte[] CalculateMessageValue(Vector p)
        {
            byte[] bytes = BitConverter.GetBytes((int) p.X);
            byte[] buffer2 = BitConverter.GetBytes((int) p.Y);
            return new byte[] { bytes[1], bytes[0], buffer2[1], buffer2[0] };
        }

        private Vector CalculateRawCoordinates(Vector coordinates)
        {
            string displayOrientation = this.displayOrientation;
            if (((displayOrientation != null) && (displayOrientation != "topleft")) && (((displayOrientation != "topright") && (displayOrientation != "bottomleft")) && (displayOrientation == "bottomright")))
            {
                coordinates.X = (this.screenWidth - 1) - coordinates.X;
                coordinates.Y = (this.screenHeight - 1) - coordinates.Y;
            }

            //// NOTE: 22.08.2012 Evo SW has a new feature now that "eats" the keypresses if two or more presses are hit to same touch coordinates.
            //// Therefore it has been agreed that touch driver will do a little randomization for the coordinates to simulate real human touch usage.
            //// It is not a big possibility to hit the same touch coordinate sequentially by hand.
            // coordinates = randomizeCoordinates(coordinates);

            int coordX = (int) (this.xMin + (coordinates.X * this.stepX));
            int coordY = (int) (this.yMin + (coordinates.Y * this.stepY));

            if (coordX > this.xMax)
            {
                coordX = (int)this.xMax;
            }
            else if (coordX < this.xMin)
            {
                coordX = (int)this.xMin;
            }
            if (coordY > this.yMax)
            {
                coordY = (int)this.yMax;
            }
            else if (coordY < this.yMin)
            {
                coordY = (int)this.yMin;
            }
            return new Vector((double) coordX, (double) coordY);
        }

        /// <summary>
        /// NOTE: 22.08.2012 Evo SW has a new feature now that "eats" the keypresses if two or more presses are hit to same touch coordinates.
        /// Therefore it has been agreed that touch driver will do a little randomization for the coordinates to simulate real human touch usage.
        /// It is not a big possibility to hit the same touch coordinate sequentially by hand.
        /// </summary>
        /// <param name="coordinates"></param>
        /// <returns></returns>
        private Vector randomizeCoordinates(Vector coordinates)
        {
            if (lastX == (int)coordinates.X && lastX != -1)
            {
                if (lastX == this.screenWidth)
                {
                    lastX --;
                }
                else
                {
                    lastX++;
                }
                coordinates.X = lastX;
            }
            else
            {
                this.lastX = (int)coordinates.X;
            }
            if (lastY == (int)coordinates.Y && lastY != -1)
            {
                if (lastY == (int)this.screenHeight)
                {
                    lastY--;
                }
                else
                {
                    lastY++;
                }
                coordinates.Y = lastY;
            }
            else
            {
                this.lastY = (int)coordinates.Y;
            }

            return coordinates;
        }

        private byte[] CalculateCyMessage(CyFingersState fs)
        {
            return this.CalculateCyMessage(fs.GetFingerState(1), fs.GetFingerState(1));
        }

        private byte[] CalculateCyMessage(FingerState finger1, FingerState finger2)
        {
            byte[] buffer = this.CalculateMessageValue(finger1.Coordinates);
            byte[] buffer5;
            if (this.hwRevision == "Aqua_F1")
            {
                buffer5 = new byte[0x20];
            }
            else
            {
                buffer5 = new byte[0x10];
            }
            buffer5[2] = 1;
            buffer5[3] = buffer[0];
            buffer5[4] = buffer[1];
            buffer5[5] = buffer[2];
            buffer5[6] = buffer[3];

            byte[] buffer2 = buffer5;

            if (this.hwRevision == "Aqua_F1")
            {
                buffer2[4] = buffer[1];
                buffer2[7] = 0x15;
                buffer2[8] = 0x10;
            }

            if (finger2.FingerPressed)
            {
                byte[] buffer3 = buffer;
                buffer3 = this.CalculateMessageValue(finger2.Coordinates);
                buffer2[2] = 1;
                buffer2[9] = buffer3[0];
                buffer2[10] = buffer3[1];
                buffer2[11] = buffer3[2];
                buffer2[12] = buffer3[3];
            }
            return buffer2;
        }

        public void SetFingerStatePressed(Vector p, int finger)
        {
            if ((((p.X < 0.0) || (p.X > this.screenWidth)) || (p.Y < 0.0)) || (p.Y > this.screenHeight))
            {
                throw new ArgumentOutOfRangeException();
            }
            if ((finger > this.numberOfFingers) && (finger < 1))
            {
                throw new ArgumentException("Number of finger should be between 1 and " + this.numberOfFingers);
            }
            this.currentCyFingersState.AddFinger(new FingerState(this.CalculateRawCoordinates(p), true), finger);
        }

        public byte[] CurrentFingersMessage
        {
            get
            {
                return this.CalculateCyMessage(this.currentCyFingersState);
            }
        }

        public int DefaultSpeed
        {
            get
            {
                return this.defaultSpeed;
            }
            set
            {
                this.defaultSpeed = value;
            }
        }
    }
}

