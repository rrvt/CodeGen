# CodeGen

Produce  c++ Modules so that an application may read and write to a MS Access Database Table.
It does this by opening an Access database,
reading the list of tables for the db and allowing the user to pick which tables to generate code for.
By the way my definition of a module is: "a module is composed of a header file, ‹moduleName›.h,
and a body file, <moduleName>.cpp and defines zero or more enums, constants, typedefs, functions,
classes, templates, etc.

## What Will It Do?

  - Open Database -- Opens the database file and shows the names of the tables in the window
  - Create Map Modules -- Provides a list of tables, select one and the program will produce a
    header and body (cpp) file that will allow assist in reading and writing to that table in the
    database.
  - Create Table Modules -- Creates the two classes for each table in the database, one using the
    abbreviation supplied by the user.  Thie module is the primary interface between the
    c++ code and the database tables.  The actual data is stored in a c++ library map structure which
    implements a tree.  The Table class is a subclass of the Map class.
  - Create Map Data Module -- This function creates two modules, the Maps module which contains one
    object for each table and the MapData module which is included in the MapsT template to define the
    Maps object: maps.  The MapeData module is mainly responsible for initializing the in-memory storage
    for each table.
  - Display Record Fields -- Provides a list of tables and then will display the fields in a record
    of the table.

## Getting Started

CodeGen is composed of three projects and compiled with Visual Studio 2017.  The three projects are:
  - CodeGen -- Solution File is in the ...\CodeGen\CodeGen.sln\ folder.  It references the other two
    projects (Library and Installer)
  - Library -- This project produces a static library of which some object files are loaded into
    the executable and the msi (installer file)
  - Installer -- A Wix Toolset Installer.  Currently this file (Product.wxs) contains reference to only
    one file CodeGen.exe.  If you wish to change the installer then I suggest you look at WixApp.

### Prerequisites

Of course this all depends on having an Access database, a Visual Studio 2017 +/- and the ability to
debug if things don't go right.  The Extension "Wix Toolset visual Studio 2017 Extension" is also
required.  It can be found in "Tools/Extensions and Updates".  If you wish to changed the installer then
look at the WixApp.

A version of the Data Access Object dynamic library must be on your system.  The library module,
AceDao.h, contains the following lines (which you may have to change):
```
#import <C:\Program Files (x86)\Microsoft Office\root\Office16\ACEDAO.DLL> rename(_T("EOF"), _T("DaoEof"))
using namespace DAO;
```
Here is an explanation of DAO:
```
   https://en.wikipedia.org/wiki/Data_access_object
```

All the code is contained in the two directories.

### Installing

Run the "msi" installer file.

## Running the tests

There are only several menu items of interest:
  - Open Access database
  - Select Table for which code is to be generated.  Be prepared to specify each output file.  Names will be
    suggested but may be changed.
  - If a table template class module is needed (early days only) select the "Create Table Template
    Extension Module"
  - Finally select the "Create Map Data Module" which generates 4 files.  Don't change the file names of
    the files unless you wish to change a bunch of other files.

Read through the History and Some Explanation section and construct a simple test case.

## History and Some Explanation

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
for finding and adding records.  When a record in-memory is changed it must be marked as dirty so
that it may be updated in the database.  Furthermore, a record may be marked for deletion when the
database is updated.  There are also an iterator class which is patterned
after the IterT template in the Library.

The tables are loaded by the following call:
```
maps.initializeMaps(_T("Database Path"), databasePath);
```
where the DBFileKey is a key for saving the path in an "ini" file and the databasePath is the complete
path to the
database.  initializeMaps is a function that is part of the template MapsT.  MapsT needs the MapData class
to complete its ability to function.  There is only one maps in a program and it is global.  Once this
function completes the database is now within the c++ program.

Each "Map" module provides a "Map" class.  A daughter class is also created by CodeGen that serves as a
table class to be used by the c++ application.  The "Map" class methods are mostly protected leaving the
table classes as the interface to the data in the database.

## Updates

### Update - 2/3/21

Reworked the modules extensively to hide as much as possible and make the interface as transparent as
possible.  Added a help file that describes both CodeGen and a bit about including the modules in an
application to use them to access and Access database.

### Update Earlier

Most of the changes were to the Library which impacted CodeGen files.

Library Changes:
  * CApp includes a function to identify the application to Windows.
  * CApp requires the application's "this" pointer at initialization.
  * CApp includes inline functions for retrieving a pointer to the document object and view object
  * The library now contains logic to manage the actual size of fonts on the display and printed page.
  * Before the font point size was expressed as an integer 10 x font size (e.g. 120).  Now it is
    expressed as as a decimal number of the actual point size (eg. 12.0).
  * ManipT used during output was changed to remove a memory leak.
  * The Options feature was moved to the Extras and Library.  The options include an option to adjust
    the scale of the displayed and printed output.

### Update 11/25/20

Library Update.

### Update 11/09/20

Update the print/display logic to avoid the conflict between the two threads.

### Update 9/10/20
Library improvement project.  Changed the Expandable Array classes, added templates for a pointer only
class in the ExpandableP class definition.  It turned out I was defining this RcdPtr class many times
worrying about exactly how it should be defined.  So I turned it into a template, which of course then
I needed to go back and add it to all the programs.  Severl iterations later I added some documentation
and I am uploading the programs today.

### Update july 30, 2020

Mostly changing startLoop, nextItem loops to using an independent iterator.  StartLoop used an integer in
the object holding the array while the independent iterator is a class by itself and multiple iterators
may be used for the same array.  See IterT.h for details.  Other organization changes too.

I also reorganized the directories a bit and included all the sub-classes that provide standard ways to
interface to Windows and MFC.  This is an ongoing effort to organize the apps in a standard way.

## Authors

Robert R. Van Tuyl, K6RWY

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details


