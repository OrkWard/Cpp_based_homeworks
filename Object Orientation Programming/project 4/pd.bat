@if exist input.txt (
    echo please delete or rename the "input.txt" file
    pause
    exit
)

::below cases is used to test pdadd
echo Today is a nice day> input.txt
pdadd < input.txt   %end of file%
timeout /nobreak /t 1
echo Today is the same day> input.txt
echo .>> input.txt
pdadd < input.txt   %single line of '.' end%
pdadd 202204        %format error%
echo This is the next day> input.txt
pdadd 20220422 < input.txt  %specify date%
echo This is another day> input.txt
pdadd 20220423 < input.txt  %specify another date%
del input.txt

::below cases is use to test pdlist
pdlist              %usage description%
pdlist -a           %all diaries print%
pdlist 2022         %use year restrict%
pdlist 202204       %use year/month restrict%
pdlist 20220421     %use year/month/day restrict%
pdlist -r 20220421  %use reverse%
pdlist 20220421 20220423 %two date restrict%
pdlist -d           %usage error%
pdlist 20224        %date format error%
pdlist -a 202204    %symble cover%

::below cases is used to test pdshow
pdshow              %usage description%
pdshow 20220422     %normal case%
pdshow 2022         %date format error%

::below cases is used to test pdremove
pdremove            %usage description%
pdremove 20220423   %the day only have one diary%
echo 1 >input.txt
pdremove 20220421<input.txt %multiple diaries%   
pdremove 20224      %date format error%
del input.txt
pause