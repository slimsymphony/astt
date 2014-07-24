package Server;

import java.io.*;
import java.util.*;
import java.nio.channels.*;

/**
 * Class for remote file system actions 
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 *
 */
public class FileSystem {
	
	private static String m_currentSearchPattern = "*";
	
	/**
	 * Sets the current search patter for file retrieval
	 * 
	 * @param 		pattern		The search patter for file retrieval to be set as current value
	 * @since		1.0.0.0
	 */
	private static void setSearchPattern(String pattern) {
		
		m_currentSearchPattern = convertToRegex(pattern).toLowerCase();
	}
	
	/**
	 * Gets the current search patter for file retrieval
	 * 
	 * @return		The current search patter for file retrieval
	 * @since		1.0.0.0
	 */
	private static String getSearchPattern() {
		return m_currentSearchPattern;
	}
	
	/**
	 * Check if a String is either null or empty
	 * 
	 * @param 		str		A string to check
	 * @return		True is null or empty; false otherwise
	 * @since		1.0.0.0
	 */
	private static boolean isNullOrEmpty(String str) {
		return str == null || str.isEmpty();
	}
	
	/**
	 * Strips the extension away from a file name
	 * 
	 * @param 		path		A file name from which the strip the extension
	 * @return		File name without the extension
	 * @since		1.0.0.0
	 */
	private static String stripExtension (String path) {

        if (isNullOrEmpty(path)) {
        	return path;
        }

        int pos = path.lastIndexOf(".");
        if (pos == -1) {
        	return path;
        }

        return path.substring(0, pos);
    }
	
	/**
	 * Gets an extension from the file name
	 * 
	 * @param 		path		A file name from which the get the extesion
	 * @return		An extension from the file name
	 * @since		1.0.0.0
	 */
	private static String getExtension (String path) {

        if (isNullOrEmpty(path)) {
        	return path;
        }

        int pos = path.lastIndexOf(".");
        if (pos == -1) {
        	return "";
        }
        if (pos == (path.length() - 1) || pos == path.length()) {
        	return "";
        }

        return path.substring(pos + 1, path.length());
    }
	
	/**
	 * Converts a file name pattern into a regex expression
	 *  
	 * @param 		pattern		A pattern to be converted
	 * @return		Matching regex expression
	 * @since		1.0.0.0
	 */
	private static String convertToRegex(String pattern) {
		
		StringBuilder builder = new StringBuilder();
		
		for(int i = 0; i < pattern.length(); i++) {
			
			char ch = pattern.charAt(i);
			
			if (ch == '.') {
				builder.append("\\.");
			}
			else if (ch == '*') {
				builder.append(".*");
			}
			else {
				builder.append(ch);
			}
		}
		
		return builder.toString();
	}
	
	/**
	 * Combines a file/directory path from two components
	 * 
	 * @param 		item1		The first item of the upcoming combination
	 * @param 		item2		The second item of the upcoming combination
	 * @return		The combined file/directory path
	 * @since		1.0.0.0
	 */
	private static String pathCombine(String item1, String item2) {
		return new File(item1, item2).getPath();
	}
	
	/**
	 * Changes an extension from the file name, and return the file name with the new extension
	 * 
	 * @param 		path			File name/path from which to change the extension
	 * @param 		newExtension	The new file extension
	 * @return		File name with the new extension
	 * @since		1.0.0.0
	 */
	private static String changeExtension(String path, String newExtension) {
        
		if (isNullOrEmpty(path)) {
        	return path;
        }
		if (isNullOrEmpty(newExtension)) {
        	return path;
        }
				
		return new File(stripExtension(path) + "." + newExtension).getPath();
	}
	
	/**
	 * Returns the number of bytes available to this virtual machine on the partition named by 
	 * this abstract pathname. When possible, this method checks for write permissions and other 
	 * operating system restrictions and will therefore usually provide a more accurate estimate 
	 * of how much new data can actually be written than getFreeSpace(). 
	 * 
	 * The returned number of available bytes is a hint, but not a guarantee, that it is possible 
	 * to use most or any of these bytes. The number of unallocated bytes is most likely to be accurate 
	 * immediately after this call. It is likely to be made inaccurate by any external I/O operations 
	 * including those made on the system outside of this virtual machine. This method makes no guarantee 
	 * that write operations to this file system will succeed.
	 * 
	 * @param 		root		The root from which to check the usable space
	 * @return		The number of available bytes on the partition or 0L if the abstract pathname 
	 * 				does not name a partition. On systems where this information is not available, 
	 * 				this method will be equivalent to a call to getFreeSpace().
	 * 
	 * @throws 		NullPointerException
	 * @throws 		IOException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Returns the number of bytes available to this virtual machine on the partition\n" +
	 "named by this abstract pathname", since = "1.0.0.0")
	public static long getUsableSpace(String root) throws NullPointerException, IOException {
		
		if (isNullOrEmpty(root)) {
			throw new NullPointerException("root");
		}
		
		File r = new File(root);
		
		if (!r.exists()) {
			throw new IOException(root + " does not exist");
		}
		
		return r.getUsableSpace();
	}
	
	/**
	 * Returns the size of the partition named by this abstract pathname.
	 * 
	 * @param 		root		The root from which to check the total space
	 * @return		The size, in bytes, of the partition or 0L if this abstract pathname does not name a partition
	 * @throws 		NullPointerException
	 * @throws 		IOException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Returns the size of the partition named by this abstract pathname.", since = "1.0.0.0")
	public static long getTotalSpace(String root) throws NullPointerException, IOException {
		
		if (isNullOrEmpty(root)) {
			throw new NullPointerException("root");
		}
		
		File r = new File(root);

		if (!r.exists()) {
			throw new IOException(root + " does not exist");
		}
		
		return r.getTotalSpace();
	}
	
	/**
	 * Returns the number of unallocated bytes in the partition named by this abstract path name.
	 * The returned number of unallocated bytes is a hint, but not a guarantee, that it is possible 
	 * to use most or any of these bytes. The number of unallocated bytes is most likely to be accurate 
	 * immediately after this call. It is likely to be made inaccurate by any external I/O operations 
	 * including those made on the system outside of this virtual machine. This method makes no guarantee 
	 * that write operations to this file system will succeed.
	 * 
	 * @param 		root		The root from which to check the free space
	 * @return		The number of unallocated bytes on the partition or 0L if the abstract pathname does 
	 * 				not name a partition. This value will be less than or equal to the total file system 
	 * 				size returned by getTotalSpace(). 
	 * @throws 		NullPointerException
	 * @throws 		IOException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Returns the number of unallocated bytes in the partition named by this abstract path name.\n" +
	 "The returned number of unallocated bytes is a hint, but not a guarantee", since = "1.0.0.0")
	public static long getFreeSpace(String root) throws NullPointerException, IOException {
		
		if (isNullOrEmpty(root)) {
			throw new NullPointerException("root");
		}
		
		File r = new File(root);
		
		if (!r.exists()) {
			throw new IOException(root + " does not exist");
		}
		
		return r.getFreeSpace();
	}
	
	/***
	 * Sums the size of the files in a given folder. Does not work recursively on version 1.0.0.0
	 * 
	 * @param 		folderName		Name of the folder from which to sum
	 * @return		The total size of files in the folder
	 * @throws 		NullPointerException
	 * @throws 		IOException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Sums the size of the files in a given folder. Does not work recursively on version 1.0.0.0", 
			since = "1.0.0.0")
	public static long sumFolderContentsLength(String folderName) throws NullPointerException, IOException {
		
		if (isNullOrEmpty(folderName)) {
			throw new NullPointerException("fileName");
		}
		
		File folder = new File(folderName);
		
		if (!folder.exists()) {
			throw new IOException(folderName + " does not exist");
		}
		
		long total = 0;
		
		if (folder.isDirectory()) {
			//TODO: support also recursive calculation
			for (String item : retrieveFiles(folderName, "*", false)) {
				if (isFile(item)) {
					total += getLength(item);
				}
				else {
					total += sumFolderContentsLength(item);
				}
			}
		}
		
		return total;
	}
	
	/**
	 * Returns the length of the file denoted by this abstract pathname. The return value is unspecified if 
	 * this pathname denotes a folder. Where it is required to distinguish an I/O exception from the case 
	 * that 0L is returned, or where several attributes of the same file are required at the same time, then 
	 * the Files.readAttributes method may be used.
	 * 
	 * @param 		fileName	Name of the file whose size is under evaluation
	 * @return		The length, in bytes, of the file denoted by this abstract pathname, or 0L if the file does not exist. 
	 * 				Some operating systems may return 0L for pathnames denoting system-dependent entities such as devices 
	 * 				or pipes. 
	 * @throws 		NullPointerException
	 * @throws 		IOException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Returns the length of the file denoted by this abstract pathname. The return value is\n" +
	 "unspecified if this pathname denotes a folder.", since = "1.0.0.0")
	public static long getLength(String fileName) throws NullPointerException, IOException {
		
		if (isNullOrEmpty(fileName)) {
			throw new NullPointerException("fileName");
		}
		
		File file = new File(fileName);
		
		if (!file.exists()) {
			throw new IOException(fileName + " does not exist");
		}
		
		if (file.isDirectory()) {
			return 0;
		}
		
		return file.length();
	}
	
	/**
	 * Calculates a file CRC
	 * 
	 * @param 		fileName		Name of the file whose CRC to calculate
	 * @return		File CRC
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Calculates a CRC for the file", since = "1.0.0.0")
	public static int getCrc(String fileName) throws IOException, NullPointerException {
		
		if (isNullOrEmpty(fileName)) {
			throw new NullPointerException("fileName");
		}
		
		File file = new File(fileName);
		
		if (!file.exists()) {
			return -1;
		}
		
		if (file.length() == 0) {
			return -1;
		}
		
        final int FILE_CRC_INIT = 0xFFFF;
        final int FILE_CRC_SHIFT = 8;
        final int FILE_CRC_MASK = 0xFF;
        final int FILE_CRC_XOROT = 0;
        final int FILE_MAX_CRC_CHECKSUM_BUFFER_SIZE = 1024;	
        
		char[] crctable =
        {
	            0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
	            0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
	            0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
	            0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
	            0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
	            0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
	            0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
	            0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
	            0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
	            0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
	            0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
	            0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
	            0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
	            0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
	            0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
	            0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
	            0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
	            0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
	            0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
	            0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
	            0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
	            0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
	            0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
	            0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
	            0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
	            0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
	            0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
	            0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
	            0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
	            0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
	            0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
	            0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
	        };
		
		InputStream fs = null;
		
		try {
			
			fs = new FileInputStream(file);
			
			int calc_checksum = FILE_CRC_INIT;

            byte[] crc_calc_buffer = new byte[FILE_MAX_CRC_CHECKSUM_BUFFER_SIZE];

            for (int offset = 0; offset < file.length(); offset += FILE_MAX_CRC_CHECKSUM_BUFFER_SIZE)
            {
                int length = fs.read(crc_calc_buffer, 0, FILE_MAX_CRC_CHECKSUM_BUFFER_SIZE);

                if (length > 0)
                {
                    for (int i = 0; i < length; i++)
                    {
                        calc_checksum = ((int)crctable[((calc_checksum >> 24) ^ crc_calc_buffer[i]) & FILE_CRC_MASK]
                            ^ (calc_checksum << FILE_CRC_SHIFT));
                    }

                    calc_checksum = (calc_checksum ^ FILE_CRC_XOROT);
                }
            }		
			
			return (int)(0xFFFF & calc_checksum);
			
		} finally {
			if (fs != null) {
				fs.close();
			}
		}
	}
	
	/**
	 * Moves the file denoted by this abstract pathname. Many aspects of the behavior of this 
	 * method are inherently platform-dependent: The move operation might not be able to move a file 
	 * from one filesystem to another, it might not be atomic, and it might not succeed if a file with 
	 * the destination abstract pathname already exists. The return value should always be checked to 
	 * make sure that the rename operation was successful. 
	 * 
	 * Note that the Files class defines the move method to move or rename a file in a platform independent manner.
	 *
	 * @param 		sourcePhoneFile			The name of the file to be moved
	 * @param 		destinationPhoneFile	The file name of the file			
	 * @return		True is successfully moved; false otherwise
	 * @throws		NullPointerException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Moves the file according to these abstract pathnames.", since = "1.0.0.0")
	public static boolean move(String sourcePhoneFile, String destinationPhoneFile) throws NullPointerException {
		
		if (isNullOrEmpty(sourcePhoneFile)) {
			throw new NullPointerException("sourcePhoneFile");
		}
		
		if (isNullOrEmpty(destinationPhoneFile)) {
			throw new NullPointerException("destinationPhoneFile");
		}
		
		File source = new File(sourcePhoneFile);
		
		if (!source.exists()) {
			return false;
		}
		
		File destination = new File(destinationPhoneFile);
		
		if (destination.exists()) {
			destination.delete();
		}
		
		return source.renameTo(destination);
	}
	
	/**
	 * Copies/duplicates a file inside the file system; ads a postfix to a new file if a file with the same name already 
	 * exists in the destination folder
	 * 
	 * @param 		sourcePhoneFile			Name of the source file to be copied/duplicated
	 * @param 		destinationPhoneFile	Name of the copy/duplicate
	 * @return		Full name of the new copy/duplicate
	 * @throws 		IOException
	 * @throws 		NullPointerException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Copies/duplicates a file inside the file system; ads a postfix to a new file if a file\n" +
	 "with the same name already exists in the destination folder", since = "1.0.0.0")
	public static String copy(String sourcePhoneFile, String destinationPhoneFile) throws IOException, NullPointerException {
		
		if (isNullOrEmpty(sourcePhoneFile)) {
			throw new NullPointerException("sourcePhoneFile");
		}
		if (isNullOrEmpty(destinationPhoneFile)) {
			throw new NullPointerException("destinationPhoneFile");
		}
		
		if (sourcePhoneFile.equals(destinationPhoneFile)) {
			return destinationPhoneFile;
		}
		
		String duplicateFilePath = destinationPhoneFile;
		
		File destination = new File(destinationPhoneFile);
		
		int num = 1;
		
		while (fileExists(duplicateFilePath))
		{
			if (getCrc(duplicateFilePath) == getCrc(sourcePhoneFile)) {
				return duplicateFilePath;
			}
			duplicateFilePath = String.format("%s(%s)", stripExtension(destination.getName()), num);
			duplicateFilePath = pathCombine(destination.getParent(), duplicateFilePath);
			duplicateFilePath = changeExtension(duplicateFilePath, getExtension(destinationPhoneFile));
			num++;
		}
		
		File source = new File(sourcePhoneFile);
		destination = new File(duplicateFilePath);
		
		if (destination.createNewFile()) {
			FileChannel src = null;
			FileChannel dest = null;
			
		    try {
		        src = new FileInputStream(source).getChannel();
		        dest = new FileOutputStream(destination).getChannel();
		        dest.transferFrom(src, 0, src.size());
		    }
		    finally {
		        if(src != null) {
		            src.close();
		        }
		        if(dest != null) {
		            dest.close();
		        }
		    }
		}
	    if (destination.length() != source.length()) {
	    	throw new IOException("Te size of destination file does not match the size of source file");
	    }
	    return duplicateFilePath;
	}
	
	/**
	 * Atomically creates a new, empty file named by this abstract pathname if and only if a file with this name
	 * does not yet exist. The check for the existence of the file and the creation of the file if it does not exist
	 * are a single operation that is atomic with respect to all other filesystem activities that might affect the file.
	 * Note: this method should not be used for file-locking, as the resulting protocol cannot be made to work reliably.
	 * The FileLock facility should be used instead.
	 * 
	 * @param 		fileName		Name of the new file
	 * @return		True if the named file does not exist and was successfully created; false if the named file already exists 
	 * @throws 		IOException
	 * @throws		NullPointerException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Atomically creates a new, empty file named by this abstract pathname if and only if a file\n" +
	 "with this name  does not yet exist", since = "1.0.0.0")
	public static boolean createFile(String fileName) throws IOException, NullPointerException {
		
		if (isNullOrEmpty(fileName)) {
			throw new NullPointerException("fileName");
		}
		
		File file = new File(fileName);
		
		return file.createNewFile() && file.exists();
	}
	
	/**
	 * Creates the folder named by this abstract pathname, including any necessary but nonexistent 
	 * parent folders. Note that if this operation fails it may have succeeded in creating some of 
	 * the necessary parent folders.
	 * 
	 * @param		folderName		Name of the folder to be created
	 * @return		true if and only if the directory was created, along with all necessary parent directories; false otherwise
	 * @throws		NullPointerException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Creates the folder named by this abstract pathname, including any necessary but nonexistent\n" + 
	 "parent folders.", since = "1.0.0.0")
	public static boolean createFolder(String folderName) throws NullPointerException {
		
		if (isNullOrEmpty(folderName)) {
			throw new NullPointerException("folderName");
		}
		
		File file = new File(folderName);
		
		if (file.exists()) {
			return true;
		}
		
		return file.mkdirs() && file.exists();
	}
	
	/***
	 * Deletes the file denoted by this abstract pathname.
	 * 	
	 * @param 		fileName		Name of the file
	 * @return		True if successfully deleted, false otherwise
	 * @throws 		NullPointerException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Deletes the file denoted by this abstract pathname.", since = "1.0.0.0")
	public static boolean deleteFile(String fileName) throws NullPointerException {
		
		if (isNullOrEmpty(fileName)) {
			throw new NullPointerException("fileName");
		}
		
		File file = new File(fileName);
		
		if (!file.exists()) {
			return true;
		}
		
		if (!file.isFile()) {
			return false;
		}
				
		return file.delete() && !file.exists();
	}
	
	/**
	 * Deletes the empty folder denoted by this abstract pathname. The folder
	 * must be empty in order to be deleted.
	 * 
	 * @param 		folderName		Name of the folder
	 * @return		True if successfully deleted, false otherwise
	 * @throws		NullPointerException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Deletes the empty folder denoted by this abstract pathname.", since = "1.0.0.0")
	public static boolean deleteFolder(String folderName) throws NullPointerException {
		
		if (isNullOrEmpty(folderName)) {
			throw new NullPointerException("folderName");
		}
		
		File file = new File(folderName);
		
		if (!file.exists()) {
			return true;
		}
		
		if (!file.isDirectory()) {
			return false;
		}
				
		return file.delete() && !file.exists();
	}
	
	/**
	 * Checks whether a file with given name exists
	 * 
	 * @param 		fileName		Name of the file
	 * @return		True if exists; false otherwise
	 * @throws		NullPointerException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Checks whether a file with given name exists", since = "1.0.0.0")
	public static boolean fileExists(String fileName) throws NullPointerException {
		
		if (isNullOrEmpty(fileName)) {
			throw new NullPointerException("fileName");
		}
		
		File file = new File(fileName);
		
		return file.exists() && file.isFile();
	}
	
	/**
	 * Checks if a file with given name is really a file
	 * 
	 * @param 		fileName		Name of the file
	 * @return		True if file; false otherwise
	 * @throws		NullPointerException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Checks if a file with given name is really a file", since = "1.0.0.0")
	public static boolean isFile(String fileName) throws NullPointerException {
		
		return fileExists(fileName);
	}
	
	/**
	 * Checks if a folder with given name is really a folder
	 * 
	 * @param 		folderName		Name of the folder
	 * @return		True if folder; false otherwise
	 * @throws		NullPointerException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Checks if a folder with given name is really a folder", since = "1.0.0.0")
	public static boolean isFolder(String folderName) throws NullPointerException {
		
		return folderExists(folderName);
	}
	
	/**
	 * Checks whether a folder with given name exists
	 * 
	 * @param 		folderName		Name of the folder
	 * @return		True if exists; false otherwise
	 * @throws		NullPointerException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Checks whether a folder with given name exists", since = "1.0.0.0")
	public static boolean folderExists(String folderName) throws NullPointerException {
		
		if (isNullOrEmpty(folderName)) {
			throw new NullPointerException("folderName");
		}
		
		File file = new File(folderName);
		
		return file.exists() && file.isDirectory();
	}
	
	/**
	 * Gets the available roots
	 * 
	 * @return		An array of available roots
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Gets the available roots", since = "1.0.0.0")
	public static String[] getRoots() {
		
		List<String> list = new ArrayList<String>();
		for(File r : File.listRoots()) {
			list.add(r.getAbsolutePath());
		}
		
		return list.toArray(new String[list.size()]);
	}
	
	/**
	 * Gets the list of files under a folder
	 * 
	 * @param 		path				Name of the folder from which to look for
	 * @return		An array of file names under the given folder
	 * @throws		NullPointerException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Gets the list of files under a folder", since = "1.0.0.0")
	public static String[] retrieveFiles(String path) throws NullPointerException {
		
		return retrieveFiles(path, "*", false);
	}
	
	/**
	 * Gets the list of files under a folder
	 * 
	 * @param 		path				Name of the folder from which to look for
	 * @param 		searchPattern		Pattern which must match with each file
	 * @return		An array of file names under the given folder
	 * @throws		NullPointerException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Gets the list of files under a folder", since = "1.0.0.0")
	public synchronized static String[] retrieveFiles(String path, String searchPattern)throws NullPointerException {
		
		return retrieveFiles(path, searchPattern, false);
	}
	
	/**
	 * Gets the list of files under a folder
	 * 
	 * @param 		path				Name of the folder from which to look for
	 * @param 		searchRecursively	NOT Supported in version 1.0.0.0
	 * @return		An array of file names under the given folder
	 * @throws		NullPointerException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Gets the list of files under a folder", since = "1.0.0.0")
	public synchronized static String[] retrieveFiles(String path, boolean searchRecursively) throws NullPointerException {
		
		return retrieveFiles(path, "*", searchRecursively);
	}
		
	/**
	 * Gets the list of files under a folder
	 * 
	 * @param 		path				Name of the folder from which to look for
	 * @param 		searchPattern		Pattern which must match with each file
	 * @param 		searchRecursively	NOT Supported in version 1.0.0.0
	 * @return		An array of file names under the given folder
	 * @throws		NullPointerException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Gets the list of files under a folder", since = "1.0.0.0")
	public synchronized static String[] retrieveFiles(String path, String searchPattern, 
			boolean searchRecursively) throws NullPointerException {
		
		if (isNullOrEmpty(path)) {
			throw new NullPointerException("path");
		}
		
		File file = new File(path);
		setSearchPattern(searchPattern);
		
		FilenameFilter fileFilter = new FilenameFilter() {
			public boolean accept(File dir, String name) {
				String pattern = getSearchPattern();
				if (isNullOrEmpty(pattern)) {
					return true;
				}
				String lowercaseName = name.toLowerCase();
				if (lowercaseName.matches(pattern)) {
					return true;
				} else {
					return false;
				}
			}
		};
		
		if (file.exists() && file.isDirectory()) {
			return file.list(fileFilter);
		}
		
		return null;
	}
	
	/**
	 * Returns the time that the file denoted by this abstract pathname was last modified.
	 * Where it is required to distinguish an I/O exception from the case where 0L is returned, 
	 * or where several attributes of the same file are required at the same time, or where the 
	 * time of last access or the creation time are required, then the Files.readAttributes method 
	 * may be used.
	 * 
	 * @param 		fileName		Name of the file whose last modification time is under interest
	 * @return		A long value representing the time the file was last modified, measured in milliseconds 
	 * 				since the epoch (00:00:00 GMT, January 1, 1970), or 0L if the file does not exist or if an 
	 * 				I/O error occurs 
	 * @throws 		IOException
	 * @throws 		NullPointerException
	 * @since		1.0.0.0
	 */
	@RPCMethod(description = "Returns the time that the file denoted by this abstract pathname was last modified.", since = "1.0.0.0")
	public static long getLastModifiedTime(String fileName) throws IOException, NullPointerException {
		
		if (isNullOrEmpty(fileName)) {
			throw new NullPointerException("fileName");
		}
		
		File file = new File(fileName);
		
		if (!file.exists()) {
			throw new IOException(fileName + " does not exist");
		}
		
		return file.lastModified();
	}
}
