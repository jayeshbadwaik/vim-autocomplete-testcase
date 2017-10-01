import os
import ycm_core
import subprocess
import glob

flags = [
# You 100% do NOT need -DUSE_CLANG_COMPLETER in your flags; only the YCM
# source code needs it.
'-DUSE_CLANG_COMPLETER',
# THIS IS IMPORTANT! Without a "-std=<something>" flag, clang won't know which
# language to use when compiling headers. So it will guess. Badly. So C++
# headers will be compiled as C headers. You don't want that so ALWAYS specify
# a "-std=<something>".
# For a C project, you would set this to something like 'c99' instead of
# 'c++11'.
'-std=c++14',
# ...and the same thing goes for the magic -x option which specifies the
# language that the files to be compiled are written in. This is mostly
# relevant for c++ headers.
# For a C project, you would set this to 'c' instead of 'c++'.
'-x',
'c++',
]

SOURCE_EXTENSIONS = [ '.cpp', '.cxx', '.cc', '.c', '.m', '.mm', '.impl']

def DirectoryOfThisScript():
  return os.path.dirname( os.path.abspath( __file__ ) )

def MakeRelativePathsInFlagsAbsolute( flags, working_directory ):
  if not working_directory:
    return list( flags )
  new_flags = []
  make_next_absolute = False
  path_flags = [ '-isystem', '-I', '-iquote', '--sysroot=' ]
  for flag in flags:
    new_flag = flag

    if make_next_absolute:
      make_next_absolute = False
      if not flag.startswith( '/' ):
        new_flag = os.path.join( working_directory, flag )

    for path_flag in path_flags:
      if flag == path_flag:
        make_next_absolute = True
        break

      if flag.startswith( path_flag ):
        path = flag[ len( path_flag ): ]
        new_flag = path_flag + os.path.join( working_directory, path )
        break

    if new_flag:
      new_flags.append( new_flag )
  return new_flags


def IsHeaderFile( filename ):
  extension = os.path.splitext( filename )[ 1 ]
  return extension in [ '.h', '.hxx', '.hpp', '.hh', '.impl' ]

def GetIncludeTemplateDeclaration( filename ):
  # Get the Directory Prefix
  prefix = os.path.dirname(filename)
  # Get the Basename
  basename = os.path.basename(filename);
  # Separate Basename into Name and Extension
  baseroot, ext = os.path.splitext(basename)
  if ext == '.impl' :
    # Split from the First Underscore
    headerroot = baseroot.split('_')[0]
    # Header File Name
    headerfilename = headerroot + ".hh"
    # absolute path for header file
    headerfilepath  = os.path.join(prefix,headerfilename)
    # Return headerfilepath
    print(headerfilepath)
    return [ '-include', headerfilepath]
  return []

def FlagsForFile( filename, **kwargs ):
  output = subprocess.check_output("gcc -dumpversion", shell=True)
  output_string = output.decode("utf-8")
  output_string = output_string.strip("\n")
  version = "-I/usr/include/c++/" + output_string
  flags.append(version)

  flags.extend( GetIncludeTemplateDeclaration( filename ) )
  relative_to = DirectoryOfThisScript()
  final_flags = MakeRelativePathsInFlagsAbsolute( flags, relative_to )
  print(final_flags)
  return {
    'flags': final_flags,
    'do_cache': True
  }
