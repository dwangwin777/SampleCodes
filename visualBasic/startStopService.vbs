'http://www.itninja.com/question/how-do-i-stop-start-service-in-vbscript
'Start Service
strServiceName = "Alerter"
Set objWMIService = GetObject("winmgmts:{impersonationLevel=impersonate}!\\.\root\cimv2")
Set colListOfServices = objWMIService.ExecQuery ("Select * from Win32_Service Where Name ='" & strServiceName & "'")
For Each objService in colListOfServices
    objService.StartService()
Next


'Stop Service
strServiceName = "Alerter"
Set objWMIService = GetObject("winmgmts:{impersonationLevel=impersonate}!\\.\root\cimv2")
Set colListOfServices = objWMIService.ExecQuery("Select * from Win32_Service Where Name ='" & strServiceName & "'")
For Each objService in colListOfServices
    objService.StopService()
Next
''''''''''''''''''''''''
Stop a service:

Option Explicit
On Error Resume Next
Public Sub StartApplication(App, WindowStyle)
dim aShell
set aShell= CreateObject("WScript.Shell")
aShell.Run App,WindowStyle
set ashell=nothing
end sub

StartApplication "%SYSTEMROOT%\system32\sc.exe stop YOUR SERVICE HERE",0
on error goto 0

'''''''''''''''''''''''''''
Delete a service:

Option Explicit
On Error Resume Next
Public Sub StartApplication(App, WindowStyle)
dim aShell
set aShell= CreateObject("WScript.Shell")
aShell.Run App,WindowStyle
set ashell=nothing
end sub

StartApplication "%SYSTEMROOT%\system32\sc.exe delete YOUR SERVICE HERE",0
on error goto 0

''''''''''''''''''''''
option explicit
Dim objShell
set objShell = WScript.CreateObject("WScript.Shell")
objShell.run("net stop ""symantec antivirus""")
objShell.run("net stop defwatch")
objShell.run("net stop ""next service etc""")

''''''''''''''''''''''
