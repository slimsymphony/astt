import clr

clr.AddReference('System.Drawing')
clr.AddReference('System.Design')
clr.AddReference('System.Windows.Forms')

from System.Drawing.Design import UITypeEditor, UITypeEditorEditStyle
from System.Windows.Forms import OpenFileDialog, DialogResult
from System import Environment

class PMDFileNameEditor(UITypeEditor) :
           
    def GetEditStyle(self, context) :

        return UITypeEditorEditStyle.Modal
    
    def EditValue(self, context, provider, value) :

        dialog = OpenFileDialog()
        dialog.Filter = "MP3 files (*.mp3)|*.mp3|All files (*.*)|*.*"
        dialog.InitialDirectory = Environment.SpecialFolder.Recent.ToString();
        
        if dialog.ShowDialog() == DialogResult.OK :
            value = dialog.FileName
        
        dialog.Dispose()
        
        return value

class MP3FileToPlay(object) :
    DisplayName = 'MP3 File to be played'
    Description = 'File path to MP3 file to be copied and played.'
    Category = 'Musick'
    DefaultValue = r'c:\David Hasselhoff - Jump in my car.mp3'
    Editor = PMDFileNameEditor()

class AACFileToPlay(object) :
    Description = 'File path to AAC file to be copied and played.'
    Category = 'Musick'
    DefaultValue = r'c:\Nirvana - Smells Like Teen Spirit.aac'

class CalculateVideoFps(object) :
    DisplayName = 'Enable Video FPS calculation'
    Description = 'Calculates video FPS from blx log'
    Category = 'Video Decoding'
    DefaultValue = False

class DuplicateSettingName(object) :
    DefaultValue = {"Yeah" : [10, "xsxsxsxsxsxsxsxsxsxsxsxssxs"] } 
    #{"abc" : 10, "def" : [10, False]}#, 10, False ] 
    #{"test" : 10, "test2" : 20}
    #['Value with', 'xyz' ], 'same name exists', 'also in other', 'setting file'
    Save = False

class DictionarySetting(object) :
    DefaultValue = { "Granma" : 
                        { "Child" : 
                            { "GrandChild" : 16 }
                         } 
                    }

