# bus-reservation-system
It is a desktop application developed in CodeBlocks compiler in Windows using C++ language.

This project mainly uses the concept of classes and objects, and file handling. A binary file 'Buses_record.dat' is created
when the user enters a new bus for the first time. Whenever the user enters a new bus, a method of the class is called and
the bus information is strored in an object of the class. This object is then written as a record in the binary file. All the
information entered by the user thereafter, is stored in that binary file, such as, the seats of each bus is stored using
2 dimensional arrays.

It depicts a simple Bus Reservation System which has options for -
inserting a new bus in the system (writing an record),
seat reservation (searching and modifying a record),
seat enquiry (retrieving a record),
buses enquiry (retrieving a record),
bus removal (deleting a record),
clearing the buses (deletes the contents of file).

It has some necessary validation checks like checking if there exist a bus with the entered bus number while using seat reservation.
