package Server;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import android.os.FileObserver;

/***
 * 
 * @author Sami
 *
 */
public class DirectoryObserver {
	
	private static DirectoryObserver m_instance = null;
		
	private HashMap<String, List<String>> m_clients = new HashMap<String, List<String>>();
	
	private HashMap<String, FileObserver> m_observers = new HashMap<String, FileObserver>();
	
	/***
	 * 
	 */
	private DirectoryObserver() 
	{ }
		
	/***
	 * 
	 * @return
	 */
	public static DirectoryObserver getInstance() {
		
		if (m_instance == null) {
			m_instance = new DirectoryObserver();
		}
		
		return m_instance;
	}
	
	/***
	 * 
	 * @param timestamp
	 * @param event
	 * @param directory
	 * @param file
	 */
	private void onFileCreated(long timestamp, int event, String directory, String file) {
		
		DirectoryObserverEvent args = new DirectoryObserverEvent();
		args.EventTime = timestamp;
		args.ChangeType = event;
		args.FileName = file;
		args.Directory = directory;
		RPCServer.getInstance().broadcastEvent(args);
	}
	
	/***
	 * 
	 * @param directory
	 * @param guid
	 */
	public boolean startObserving(final String directory, String guid) {
		
		if (directory != null && !directory.isEmpty() && guid != null && !guid.isEmpty()) {
			File dir = new File(directory);
			if (dir.exists() && dir.isDirectory()) {
				
				if (!m_observers.containsKey(directory)) {
					
					try {
						FileObserver observer = new FileObserver(directory) {
						
							@Override
							public void onEvent(int event, String file) {
								onFileCreated(System.currentTimeMillis(),
										event,
										directory,
										file);
							}
						};
						
						observer.startWatching();
						m_observers.put(directory, observer);
						
					} catch (Exception e) {
						Trace.writeLine(e);
						return false;
					}
				}
				if (m_clients.containsKey(directory)) {
					List<String> guids = m_clients.get(directory);
					if (!guids.contains(guid)) {
						guids.add(guid);
					}
				}
				else {
					List<String> guids = new ArrayList<String>();
					guids.add(guid);
					m_clients.put(directory, guids);
				}
				
				return true;
			}
		}
		
		return false;
	}
	
	/***
	 * 
	 * @param directory
	 * @param guid
	 */
	public boolean stopObserving(String directory, String guid) {
		
		boolean retVal = false;
		
		if (directory != null && directory != null && guid != null && !guid.isEmpty() &&
				m_clients.containsKey(directory) && m_observers.containsKey(directory)) {
			List<String> guids = m_clients.get(directory);
			if (guids.contains(guid)) {
				retVal = guids.remove(guid);
				if (guids.size() == 0 ) {
					m_observers.get(directory).stopWatching();
					m_observers.remove(directory);
				}
			}
		}
		
		return retVal;
	}
}

