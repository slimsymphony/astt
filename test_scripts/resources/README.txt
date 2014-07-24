Insert any data files needed by test scripts under the resources directory.
Then they can be easily accessed from the scripts with resources(filename) command.
Files can be contained in sub-directories as long as the directories are located under resources directory.

For example:
resources/Applications
resources/Contacts
resources/Messages
resources/Music
resources/Images/Photos
resources/Images/Landscape
resources/Images/Icons
etc.

Resources command will search for a resource directory from the current script directory all the way up to the drive root.
If the resources directory is found, then the given filename is searched recursively through all the directories inside the resources directory.
