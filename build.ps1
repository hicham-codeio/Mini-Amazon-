# Mini Amazon C++ E-Commerce System - Build Script for Windows PowerShell
# This script compiles the project using g++ compiler

param(
    [ValidateSet('build', 'clean', 'rebuild')]
    [string]$Action = 'build'
)

# Configuration
$env:PATH = "C:\Qt\Tools\CMake_64\bin;C:\Qt\Tools\Ninja;C:\Qt\Tools\mingw1310_64\bin;C:\Qt\6.11.0\mingw_64\bin;" + $env:PATH
$OUTPUT = '.\build\MiniAmazonGUI.exe'

function Build {
    Write-Host ""
    Write-Host "Building Mini Amazon Qt Application..." -ForegroundColor Green
    Write-Host ""
    
    if (-Not (Test-Path build)) {
        New-Item -ItemType Directory -Path build | Out-Null
    }
    Set-Location build
    cmake -G Ninja -DCMAKE_PREFIX_PATH="C:\Qt\6.11.0\mingw_64" ..
    ninja
    $ninjaExitCode = $LASTEXITCODE
    Set-Location ..
    
    if ($ninjaExitCode -eq 0) {
        Write-Host ""
        Write-Host "BUILD SUCCESSFUL!" -ForegroundColor Green
        Write-Host ""
        Write-Host "Run the application with: $OUTPUT"
        Write-Host ""
    } else {
        Write-Host ""
        Write-Host "BUILD FAILED! Please check the errors above." -ForegroundColor Red
        Write-Host ""
        exit 1
    }
}

function Clean {
    Write-Host "Cleaning build artifacts..." -ForegroundColor Yellow
    if (Test-Path build) {
        Remove-Item -Recurse -Force build
        Write-Host "Deleted build directory" -ForegroundColor Green
    } else {
        Write-Host "No artifacts to clean." -ForegroundColor Gray
    }
}

# Execute requested action
switch ($Action) {
    'build' { Build }
    'clean' { Clean }
    'rebuild' { Clean; Build }
}
