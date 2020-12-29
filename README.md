<head>
    <p align="center">
        <h2 align="center">This is my repo for my implementation of UNIX utility "ls".</h2>
    </p>
</head>

## Building the program
<ol>
    <li>Download the source code from this repository.</li>
    <li>Go to the program directory.</li>
    <li>Run <code>make</code> in terminal.</li><br>
</ol>
<b>Attention! This program only works with OSX systems!</b>

## Usage
`uls [-ACGRSTcfglmortux1] [file ...]`<br>
For example: `./uls -l test`

### Usable Flags
`-A`  List all entries except for . and ...  Always set for the superuser.  
`-C`  Force multi-column output; this is the default when output is to a terminal.  
`-G`  Makes output colorful and fancy.  
`-R`  Recursively list subdirectories encountered.  
`-S`  Sort files by size.  
`-T`  When used with the -l option, display complete time information for the file, including month, day, hour, minute, second, and year.  
`-c`  Use time when file status was last changed for sorting (-t) or long printing (-l).
`-g`  This option is only available for compatibility with POSIX; it isused to display the group name in the long (-l) format output.  
`-l`  For each file, print the file's file serial number.  
`-m`  Stream output format; list files across the page, separated by commas.  
`-o`  List in long format, but omit the group id.  
`-r`  Reverse the order of the sort to get reverse lexicographicalorder or the oldest entries first (or largest files last, if combined with sort by size.  
`-t`  Sort by time modified (most recently modified first) before sorting the operands by lexicographical order.  
`-u`  Use time of last access, instead of last modification of the file for sorting (-t) or long printing (-l).  
`-x`  The same as -C, except that the multi-column output is produced with entries sorted across, rather than down, the columns.  
`-1`  Force output to be one entry per line.  This is the default when output is not to a terminal.
