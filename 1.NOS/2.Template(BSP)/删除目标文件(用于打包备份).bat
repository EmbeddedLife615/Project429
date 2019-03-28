rd /Q /S project\MDK-ARM\DebugConfig
rd /Q /S project\MDK-ARM\Listings
rd /Q /S project\MDK-ARM\Objects
rd /Q /S project\MDK-ARM\RTE
del /Q project\MDK-ARM\*.bak
del /Q project\MDK-ARM\*.dep
del /Q project\MDK-ARM\JLink*
del /Q project\MDK-ARM\*.uvopt
del /Q project\MDK-ARM\*.uvproj.*
del /Q project\MDK-ARM\*.uvguix.*

del /Q project\EWARMv6\Project.dep
del /Q project\EWARMv6\Flash
del /Q project\EWARMv6\CpuRAM
del /Q project\EWARMv6\settings
rd  /Q /S project\EWARMv6\Flash
rd /Q /S project\EWARMv6\CpuRAM
rd /Q /S project\EWARMv6\settings

