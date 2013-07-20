#############################################################################
# Makefile for building: BattleCity
# Generated by qmake (2.01a) (Qt 4.8.3) on: ?? 7? 20 14:17:48 2013
# Project:  BattleCity.pro
# Template: app
# Command: /usr/bin/qmake -o Makefile BattleCity.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/i386-linux-gnu -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = Blast.cpp \
		EnemyTank.cpp \
		main.cpp \
		Missile.cpp \
		Tank.cpp \
		TankWindow.cpp moc_TankWindow.cpp \
		qrc_resource.cpp
OBJECTS       = Blast.o \
		EnemyTank.o \
		main.o \
		Missile.o \
		Tank.o \
		TankWindow.o \
		moc_TankWindow.o \
		qrc_resource.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		BattleCity.pro
QMAKE_TARGET  = BattleCity
DESTDIR       = 
TARGET        = BattleCity

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: BattleCity.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/i386-linux-gnu/libQtGui.prl \
		/usr/lib/i386-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile BattleCity.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/i386-linux-gnu/libQtGui.prl:
/usr/lib/i386-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile BattleCity.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/BattleCity1.0.0 || $(MKDIR) .tmp/BattleCity1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/BattleCity1.0.0/ && $(COPY_FILE) --parents Blast.h EnemyTank.h MapElement.h Missile.h Tank.h TankConst.h TankWindow.h .tmp/BattleCity1.0.0/ && $(COPY_FILE) --parents resource.qrc .tmp/BattleCity1.0.0/ && $(COPY_FILE) --parents Blast.cpp EnemyTank.cpp main.cpp Missile.cpp Tank.cpp TankWindow.cpp .tmp/BattleCity1.0.0/ && (cd `dirname .tmp/BattleCity1.0.0` && $(TAR) BattleCity1.0.0.tar BattleCity1.0.0 && $(COMPRESS) BattleCity1.0.0.tar) && $(MOVE) `dirname .tmp/BattleCity1.0.0`/BattleCity1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/BattleCity1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_TankWindow.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_TankWindow.cpp
moc_TankWindow.cpp: TankConst.h \
		Blast.h \
		TankWindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) TankWindow.h -o moc_TankWindow.cpp

compiler_rcc_make_all: qrc_resource.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_resource.cpp
qrc_resource.cpp: resource.qrc \
		image/small/enemy1L.gif \
		image/small/select.png \
		image/small/p1tankU.gif \
		image/small/missile1.gif \
		image/small/blast2.gif \
		image/small/plain.gif \
		image/small/enemy1R.gif \
		image/small/blast6.gif \
		image/small/steels.gif \
		image/small/select.gif \
		image/small/symbol.gif \
		image/small/blast1.gif \
		image/small/blast5.gif \
		image/small/p1tankL.gif \
		image/small/p1tankD.gif \
		image/small/grass.gif \
		image/small/gameOver.gif \
		image/small/blast4.gif \
		image/small/blast8.gif \
		image/small/p1tankR.gif \
		image/small/walls.gif \
		image/small/blast3.gif \
		image/small/enemy1U.gif \
		image/small/blast7.gif \
		image/small/enemy1D.gif
	/usr/bin/rcc -name resource resource.qrc -o qrc_resource.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean 

####### Compile

Blast.o: Blast.cpp Blast.h \
		TankConst.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Blast.o Blast.cpp

EnemyTank.o: EnemyTank.cpp EnemyTank.h \
		Tank.h \
		TankConst.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o EnemyTank.o EnemyTank.cpp

main.o: main.cpp TankWindow.h \
		TankConst.h \
		Blast.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

Missile.o: Missile.cpp Missile.h \
		Tank.h \
		TankConst.h \
		TankWindow.h \
		Blast.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Missile.o Missile.cpp

Tank.o: Tank.cpp Tank.h \
		TankConst.h \
		EnemyTank.h \
		TankWindow.h \
		Blast.h \
		Missile.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Tank.o Tank.cpp

TankWindow.o: TankWindow.cpp TankWindow.h \
		TankConst.h \
		Blast.h \
		Tank.h \
		EnemyTank.h \
		Missile.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o TankWindow.o TankWindow.cpp

moc_TankWindow.o: moc_TankWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_TankWindow.o moc_TankWindow.cpp

qrc_resource.o: qrc_resource.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_resource.o qrc_resource.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

