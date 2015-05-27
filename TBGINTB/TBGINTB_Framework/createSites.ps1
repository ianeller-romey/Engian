$net40Path = [System.IO.Path]::Combine($env:SystemRoot, "Microsoft.NET\Framework\v4.0.30319");
$aspnetRegIISFullName = [System.IO.Path]::Combine($net40Path, "aspnet_regiis.exe");
 
if ((test-path $aspnetRegIISFullName) -eq $false)
{
    $message =  "aspnet_regiis.exe was not found in {0}. Make sure Microsoft .NET Framework 4.0 installed first." -f $net40Path;
    write-error $message;
}

$SiteName="gintub"
$SitePort=80
$SiteHost=$SiteName
$SitePath=("C:\inetpub\" + $SiteName)
$SiteLogsPath=("C:\inetpub\logs\" + $SiteName)

$ServicesName="gintubservices"
$ServicesPath=Split-Path $script:MyInvocation.MyCommand.Path
$ServicesLogsPath=("C:\inetpub\logs\" + $SiteName + "\" + $ServicesName)

$AppPool=("IIS:\AppPools\" + $SiteName)
$AppPoolIdentity=0
switch ($AppPoolIdentity)
{
    0 {$FullAppPoolIdentity="LocalSystem"}
    1 {$FullAppPoolIdentity="LocalService"}
    2 {$FullAppPoolIdentity="NetworkService"}
    3 {$FullAppPoolIdentity="SpecificUser"}
    4 {$FullAppPoolIdentity="ApplicationPoolIdentity"}
}
if ($AppPoolIdentity -eq "3") {
$AppPoolUser=Read-Host "`nPlease provide username for the ApplicationPool identity"
$AppPoolPwd=Read-Host "Please provide the password for '$AppPoolUser' user" -AsSecureString
}
 

Import-Module "WebAdministration" -ErrorAction Stop
 
# Creates the ApplicationPool
$AppPoolExists=Test-Path $AppPool
if(-Not $AppPoolExists)
{
    Write-Host "Creating website application pool" -ForegroundColor Yellow
    New-WebAppPool –Name $SiteName -Force
}
Write-Host "Updating website application pool" -ForegroundColor Yellow
Set-ItemProperty ("IIS:\AppPools\" + $SiteName) -Name processModel.identityType -Value $AppPoolIdentity
Set-ItemProperty ("IIS:\AppPools\" + $SiteName) managedRuntimeVersion v4.0
if ($Identity -eq "3") {
Set-ItemProperty ("IIS:\AppPools\" + $SiteName) -Name processModel.username -Value $AppPoolUser
Set-ItemProperty ("IIS:\AppPools\" + $SiteName) -Name processModel.password -Value $AppPoolPwd
}
 
# Creates the website
$SiteDirectoryExists=Test-Path $SitePath
if(-Not $SiteDirectoryExists)
{
    Write-Host "Creating website directory" -ForegroundColor Yellow
    New-Item -ItemType directory -Path $SitePath
}
$SiteLogsDirectoryExists=Test-Path $SiteLogsPath
if(-Not $SiteLogsDirectoryExists)
{
    Write-Host "Creating website logs directory" -ForegroundColor Yellow
    New-Item -ItemType directory -Path $SiteLogsPath
}
Write-Host "Creating website" -ForegroundColor Yellow
New-Website –Name $SiteName -Port $SitePort –HostHeader $SiteHost -PhysicalPath $SitePath -ApplicationPool $SiteName -Force
Set-ItemProperty ("IIS:\Sites\" + $SiteName) -Name logfile.directory -Value $SiteLogsPath
 
# Creates the services
$ServicesLogsDirectoryExists=Test-Path $ServicesLogsPath
if(-Not $ServicesLogsDirectoryExists)
{
    Write-Host "Creating services logs directory" -ForegroundColor Yellow
    New-Item -ItemType directory -Path $ServicesLogsPath
}
Write-Host "Creating services site" -ForegroundColor Yellow
New-WebApplication -Site $SiteName –Name $ServicesName -PhysicalPath $ServicesPath -ApplicationPool $SiteName -Force

#update hosts file
Set-HostsEntry -IPAddress 10.2.3.4 -HostName $SiteHost
 
 #start everything
Start-WebAppPool -Name $SiteName
Start-WebSite $SiteName