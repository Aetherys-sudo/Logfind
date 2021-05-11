# Logfind
Simple tool that searches for files that contain given word(s).

USAGE: "./logfind <words>"
OPTIONAL: -o (logic OR, shows files that contain at least one word)

Tool will now read all files from a specific folder named ".logfind" located under /home/user/.logfind

Tool has limited error handling at the moment. It is able look for any number of words passed on as arguments in the specified file.

Logic OR argument can be passed to the function using -o. Files that contain at least one of the provided words will now be valid.

Application can now use multiple files from a different folder. See usage . Portability is still an aspect to be improved upon. 


FUTURE UPDATES:
Performance improvement.
Portability.
Error and case handling.


