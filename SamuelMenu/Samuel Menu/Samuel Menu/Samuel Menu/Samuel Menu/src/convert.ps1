$txtPath = "c:\Users\heric\OneDrive\Desktop\hyperx clarencio\HyperX\hyperx source\src\kid.txt"
$outPath = "c:\Users\heric\OneDrive\Desktop\hyperx clarencio\HyperX\hyperx source\src\Includes\kid_image.hpp"
$content = Get-Content -Path $txtPath -Raw
$parts = $content -split '\s+' | Where-Object { $_ -ne '' }
$hexArray = $parts | ForEach-Object { "0x$_" }
$joined = $hexArray -join ', '
$result = "const unsigned char kid_png[] = { $joined };"
Set-Content -Path $outPath -Value $result
