# Normalization of UNIX path 

The class `UnixPath` with the following properties is realised:

- The constructor takes the initial current directory (absolute path), not necessarily normalized
- The class has methods
  - `ChangeDirectory` - change the directory, can take an absolute or relative path, not necessarily normalized
  - `GetAbsolutePath` - return a string corresponding to the normalized absolute path of the current directory
  - `GetRelativePath` - return a string corresponding to the normalized relative path of the current directory
  
  
  
Normalization of the path consists in bringing to an absolute path and getting rid of the following elements:

/ - at the end of the path

. - current directory

.. - parent directory

// - equivalent to /



