$Libraries = ""
$CodeFolder = "code"
$OutputFolder = "bin"
$MainFile = "main.cpp"
$ProgramName = "split_image.exe"
$compiler_flags="/Z7 /Od /Wall"
$linker_flags="/STACK:0x100000,0x100000"


$Includes = $AdditionalHeaderLocation -join " /I"
$Includes = "/I$Includes"
$rows = @()
iex "cl /nologo $Includes $compiler_flags /Fe$OutputFolder\$ProgramName /Fo$OutputFolder\ /Fm$OutputFolder\ /wd5045 /wd4514 /wd4710 /wd4820 /wd4204 $CodeFolder\$MainFile /link $Libraries $linker_flags" | ForEach-Object {$rows += $_}

# reverse error output so the first lines are displayed last
[array]::Reverse($rows)
$ofs = [Environment]::Newline
$errors = $rows | where {$_ -like "*error*"}
$warnings = $rows | where {$_ -like "*warning*"}
$rest = $rest | where {$_ -notlike "*warning*"} | where {$_ -notlike "*error*"}
if ($rest) { Write-Host "$rest" }
if ($warnings) { Write-Host "$warnings" }
if ($errors) { Write-Host "$errors" }


if ($LastExitCode -ne 0) {
   exit
}
if ($warnings.Count -gt 0) {
#	exit
}

# run the program
Push-Location .\bin
iex ".\$ProgramName $args"
Pop-Location
