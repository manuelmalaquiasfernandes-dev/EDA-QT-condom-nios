cmake_minimum_required(VERSION 3.16)

project(projeto_manuel_leticia LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(projeto_manuel_leticia main.cpp condomino.cpp fracao.cpp listacondominos.cpp listafracoes.cpp gestorCondominio.cpp Movimentos.cpp TipoMovimento.cpp)

include(GNUInstallDirs)
install(TARGETS projeto_manuel_leticia
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
