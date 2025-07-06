@echo off
echo Compilando o projeto...

gcc main.c Funcoes/AVL/funcoesAVL.c Funcoes/Rubro/funcoesRubro.c Funcoes/Utils/gerador.c Funcoes/Utils/arvoreUtils.c Funcoes/Utils/matematicas.c -o programa -Wall -g


if %errorlevel% equ 0 (
    echo Compilado com sucesso!
) else (
    echo Erro na compilação.
)
pause
