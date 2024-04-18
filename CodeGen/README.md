# CodeGen II

Produce a c++ Module (header and body file containing one or more classes or functions) for an
MS Access Database Table.  It does this by opening an Access database,
reading the list of tables for the db and allowing the user to pick which tables to generate code for.

The c++ modules may then be copied to anotherr application, compiled into the application and used to
load tables from a MS Access database into the application.  The records have field names which correspond
to the field names in the database tables (Access names the fields with Capitalized names, I've
changed the field names to uncapitalized names).  The primary key selected in CodeGen is found with
a binary search.  The fields chosen in the linear search key dialog are found with a linear search.

If a record is changed it must be "marked" as dirty and the store function called for the table in which
the record resides.  Likewise a record may be added or deleted using the appropriate functions.  Note,
each table class is a subclass of the DBtable class and each record is a subclass of the DBrcd class.
Some of the relevant functionality is in these parent classes.

## What Will It Do?

  There are three relevant commands:
  - Load the Database
  - Pick a table and create the module for it.
  - Create a DBtable class first picking the tables to include in it.

## Getting Started

CodeGen is composed of three projects and compiled with Visual Studio 2017.  The three projects are:
  - CodeGenII -- Solution File is in the ...\CodeGenII\CodeGenII\ folder.  It references the other
    three projects (Library and Installer)
  - CodeGenIIHelp -- Help file for the application.  Use the Help Workshop.
  - Library -- This project produces a static library of which some object files are loaded into
    the executable (installer file)
  - Installer -- A Wix Toolset Installer.  Currently this file (Product.wxs) contains references to
    CodeGenII.exe and the CodeGenII.chm.  If you wish to change the installer then I suggest you look
    at WixApp.

### Prerequisites

Of course this all depends on having an Access database, a Visual Studio 2017 +/- and the ability to
debug if things don't go right.  The Extension "Wix Toolset visual Studio 2017 Extension" is also
required.  It can be found in "Tools/Extensions and Updates".  If you wish to changed the installer then
look at the WixApp.

Microsoft HTML Help Workshop (last version).  This is the link to the last version:
```
https://docs.microsoft.com/en-us/previous-versions/windows/desktop/htmlhelp/microsoft-html-help-downloads
```

A version of the Data Access Object dynamic library must be on your system.  The library module,
DAOAcess, contains the following lines (which you may have to change):
```
#import <C:\Program Files (x86)\Microsoft Office\root\Office16\ACEDAO.DLL> rename(_T("EOF"), _T("DaoEof"))
using namespace DAO;
```
Here is an explanation of DAO:
```
   https://en.wikipedia.org/wiki/Data_access_object
```

All the code is contained in the two directories, CodeGenII and Library.

### Installing

Run the "msi" installer file.

## Running the tests

Read through the History and Some Explanation section and construct a simple test case.

## CodeGen II History and some Explanation

Read the CodeGen History and Some Explanation paragraphs first.  It will make what my comments here
a little easier to understand.

I wrote an article for Code Project about a couple of classes which allow a vector to expand
as necessary.  During the exercise I added a binary search capability purely because I mentioned
that it could be done.  There are two version of Expandable, one that keeps the data in the vector
and one that allocates a heap store node and the vector contains a pointer to the node.

The orginal scheme to replicate the database tables involved template <...> class map (See the link
below).  Either I made it overly complex or it was overly complex due to the interface to the map class.
So I just decided to try a different approach.  This approach involved placing the data in
and ExpandableP vector.  The data goes in a heap node and a pointer to the node goes in the
ExpandableP vector.  The data is loaded in the vector in sorted order on the primary key.  Of course
this application allows the user to pick the primary key to use in the application.  The database
has its own ideas about primary keys, but that is irrelevant to the applications.

There is one more table needed in an application that ties all the tables together.  I call the class
DBtables and the object dbTables.  The table contains a pointer to each database table object.
Each database table opbject when it initializes itself sends a pointer to the DBtables object.
But this only works when the DBtables object is initialized before all of the tables.  The DBtables
Module ensure that this is true by defining all of the relevant objects in the correct order.

Now that dbTables exists and knows about all the tables then all the tables can be loaded in
the application by a single call to dbTables.load(path);

So the purpose of this application is to allow the user to pick the database tables to replicate in
memory and create the table modules and DBtable module.

### CodeGen History and Some Explanation

A while ago (15 - 20 years?) I scheduled Dressage Horse Shows.  The mechanism provided by the Fox Village
software seemed to require too many steps.  This led me to investigate how I might improve things.

The first step was to find a way to access the database, which, conveniently was implemented in MS
Access, the older mdb files.  After some time I found that the Data Access Object mechanism would allow
read/write access to the database.  The interface was not particularly easy to use so the AceDao module
(see Library) was written.

The second step was to find a way to manipulate the records in the program.  The method chosen was to
load all the records in all the tables into a std::map.  The complete description of the c++ std::map
template is given here:
```
https://docs.microsoft.com/en-us/cpp/standard-library/map-class?view=vs-2019
```
Here are some highlights of the Standard Library map class:
  - A container of variable size that efficiently retrieves element values based on associated key values.
  - Reversible, because it provides bidirectional iterators to access its elements.
  - Sorted, because its elements are ordered by key values according to a specified comparison function.
  - Unique. because each of its elements must have a unique key.
  - A pair-associative container, because its element data values are distinct from its key values.
  - A template class, because the functionality it provides is generic and independent of element or key type. The data types used for elements and keys are specified as parameters in the class template together with the comparison function and allocator.

Notice that a map has similar properties to Access Tables.  The modules generated with the phrase "Map"
in the names provide an interface to a map that will contain all the records in the corresponding database
table.  The Map modules provide a description of the Table's records and some standard methods (functions)
for adding, modifying, finding, and deleting records.  There are also two functions for looping over all
the records, startLoop and nextRecord.

The tables are loaded by the following call:
```
maps.initializeMaps(_T("Database Path"), databasePath);
```
where the DBFileKey is a label for displaying the path and the databasePath is the complete path to the
database.  initializeMaps is a function that is part of the template MapsT.  MapsT needs the MapData class
to complete its ability to function.  There is only one maps in a program and it is global.  Once this
function completes the database is now within the c++ program.

Each "Map" file provides a "Table" class.  However it was soon discovered that the generated table
classes were not sufficient.  So a daughter class may be created by CodeGen that serves as a template for
additional or different functions for use with a table.  Tables serve a variety of purposes and only the
designer knows exactly what should and could be done with a record in a table.  This led to the creation
of the files with "Tbl" in their name.  They implement the table class that is most useful in a program
leaving the "Map" class untouched by human hands (just in case there is an improvement that must be made
in the "Map" module sometime in the future).

#### Example

In the database directory there is a simple two table database.  The program TestApp.exe can access the
database through the following Modules (.h and .cpp files) that were prepared with CodeGen:
  - BookMap
  - BookTbl
  - MapData
  - Maps
  - PersonMap
  - PersonTbl

A person may be an author or a protagonist (books main character).  There are three commands that are
related to the database:
  - Display one or both tables
  - Add a Book (Title, author and protagonist) or Add a person
  - erase a book or person (note, simple erase only erases in the table selected)

## Updates

### Update 4/12/24 & 4/18/24

Improved the way Toolbars and Window Position and size are handled.

### Update 2/16/24

Reorganized the Library so that it compiles once into Debug and Release directories under the Library
directory.

### Update 1/7/24

Library and other changes.

### Update 12/25/23

Modify ExpandableP and subsequent ripple.

### Update 12/11/23

Improve ExpandableP (modify) and associated changes.

### Update 6/26/23

Library Update.

### Update 4/11/23

Changes to the way the library handles printing are reflected in the changes to the application.

### Update 3/15/23

Complete move of orientation to reports.

### Update 3/8/23

Added numbers to notepad archive output.

Fixed (hopefully) Print and Print Preview.  See MakeApp for details.

### Update 1030/22

Start app with position and size that the app was in when it last exited.  Update the toolbar background.
Updated the help file to reflect the changes required by moving to Win11 and VS22.

### Update 8/3/22

Minor Library updates.

### Update 4/15/22

Big adventure in February when I started moving to a new Win11 and Visual Studio 2022.  I now
feel that this version is working in the new environment.  There were several changes made to the app
in order to compile properly on VS22.

The big changes are related to the interface with the MS Access database file.  The interface I was
formally using was labelled "DAO".  It has now been downgraded to obsolete (even though one can still use
it).  So I chose to try ODBC as the interface.  Through some extensive web research I found a mechanism
developed and documented by Alexander Wiseman in 2002 to load the table names and field names using ODBC.
I have been able to expand on that work to allow creation of modules by this application to read and write
to/from tables in an Access database.  The visible module is the <Table Abbr>Tbl.h module.  It is composed
of a record description and a table class that holds all the records that occur in the database.  The
intention is that the manipulation in an application is done on the in-core version of the database and
when happy with the result the in-core data is written back to the database file (actually only the
records that are marked as dirty are written).  Look at the RWracesDB for examples of the use of the
modules produced here.  RWracesDB should be available in a day or two.

### Update 01/31/22

Updates to the library, mostly about the toolbar, but also NewAllocator, and a minor addition to
Expandable.

Also scrubbed the project files to remove all references to precompiled header files which I turned off
in VS17.  Unfortnately VS does not remove all references and pch files kept cropping up.  Not only does
that slow down the compiler but the files are large...

### Update 12/18/21

While creating a template for a dialog box only application with a toolbar the Library was added to and
changed to hopefully simplify toolbar creation.  This version of the toolbar includes buttons, edit boxes,
combo boxes and drop down menus as well as the traditional 16x15 icons.

CodeGen is a tradional App and has one combo box that is filled when the database is identified.

### Update 11/13/21

The changes are in the library:

  - Expandable and ExpandableP -- moved the functions out of the class to make the compilation smaller,
also fixed one bug (or feature) in the ExpandableP insert sorted function that would throw out entries
that were already in in the array.
  - FileIO -- Changed the type of path from "String&" to "TCchar*".  It turns out that automatic
conversion from String to TCchar* is easy, but the reverse is is not easy.  Also added a function to
get the length of a file given a path.
  - FineName -- Added a function to get the directory name of from a path
  - NewAllocator -- Corrected the debug dependency from if to ifdef
  - ToolBar -- Added data for drop down menus

### Update 10/31/21

Changed Resources (i.e. xxx.rc data) access so that it will work with a dll.  Changed the logic in the
About Box code.  Some other library changes.  Some corresponding changes in the application.

### Update 10/2/21

Libray update only.

### Update 5/21/21

Added a clear function to all database so that load may be performed multiple time with different
databases.

## Authors

Robert R. Van Tuyl, K6RWY

Contact:  romeo romeo victor tango alpha tango sam whisky delta echo dot charlie oscar mike

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details


