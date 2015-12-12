+===============================================================+
|         				     EasyFTP	         			    |
|---------------------------------------------------------------|
|			Written by Anthony Spurgeon & Ryan Speets			|
+===============================================================+

A simple client/server application demonstration of browsing and 
downloading files from a server over a TCP/IP connection utilizing 
a custom wrapper of the Win32 Socket Library.

Commands - 
			dir - Lists all items in the directory
			cd	- Changes directory to the desired one
			get	- Downloads a file that you specify
			help - Displays the commands you may use
			exit - Quits the application

Usage: [Program Name] [IP-Address]


EasySocket	-	Wrapper around the Win32 Socket Library. Handles 
				sockets and interactions with the API