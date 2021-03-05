################################################################
# Qwt Widget Library
# Copyright (C) 1997   Josef Wilgen
# Copyright (C) 2002   Uwe Rathmann
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Qwt License, Version 1.0
###################################################################
CURRENT_DIR = $$PWD
include(qwtfunctions.pri)

INCLUDEPATH += $${CURRENT_DIR}/qwt_linux/src
DEPENDPATH  += $${CURRENT_DIR}/qwt_linux/src

QMAKE_RPATHDIR *= $${CURRENT_DIR}/qwt-6.1.4/lib
qwtAddLibrary($${CURRENT_DIR}/qwt-6.1.4/lib, qwt)
