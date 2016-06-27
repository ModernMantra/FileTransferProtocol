# FileTransferProtocol

It makes transfer of any file between two computers. There are
client and server codes written in C. When the transfer is complete,
mail will be received by running script. Also it is generated html 
file with transfer details such as date of transfer, duration, 
name of file transferred, ip address of server. 
In order to transfer file, follow the instructions below:
	* gcc location_of_your_server_main.c_file
	* locate the file which needs to have *.out extension
	* enter the location of file from instruction above and run it 
	* compile client main.c code by using same command gcc
	* find the location of compiled file from instruction above (i.e.  a.out)
	* run the command which should be similar to this one
	/Users/user_name/a.out ip_address_of_server /Users/user_name/happy.txt>received
	pseudocode
	location_of_client_code_*.out ip_address_of_server location_of_transfer_file_on_server>name_of_receiving_file

->FILE FIleTransferProtocol NEEDS TO BE PLACED IN htdocs IF USING XAMPP. OBVIOUSLY, LOCATION PATH OF SAME FILE NEEDS TO BE CHANGED WITHIN client -> main.c FILE
->CHANGE email address IN SCRIPT IN CLIENT FOLDER
