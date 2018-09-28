/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QPLATFORMFONTDATABASE_H
#define QPLATFORMFONTDATABASE_H

//
//  W A R N I N G
//  -------------
//
// This file is part of the QPA API and is not meant to be used
// in applications. Usage of this API may make your code
// source and binary incompatible with future versions of Qt.
//

#include <QtCore/qconfig.h>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QList>
#if QT_DEPRECATED_SINCE(5, 5)
#include <QtCore/QHash>
#endif
#include <QtGui/QFontDatabase>
#include <QtGui/private/qfontengine_p.h>
#include <QtGui/private/qfont_p.h>

QT_BEGIN_NAMESPACE


class QWritingSystemsPrivate;

class Q_GUI_EXPORT QSupportedWritingSystems
{
public:

    QSupportedWritingSystems();
    QSupportedWritingSystems(const QSupportedWritingSystems &other);
    QSupportedWritingSystems &operator=(const QSupportedWritingSystems &other);
    ~QSupportedWritingSystems();

    void setSupported(QFontDatabase::WritingSystem, bool supported = true);
    bool supported(QFontDatabase::WritingSystem) const;

private:
    void detach();

    QWritingSystemsPrivate *d;

    friend Q_GUI_EXPORT bool operator==(const QSupportedWritingSystems &, const QSupportedWritingSystems &);
    friend Q_GUI_EXPORT bool operator!=(const QSupportedWritingSystems &, const QSupportedWritingSystems &);
};

Q_GUI_EXPORT bool operator==(const QSupportedWritingSystems &, const QSupportedWritingSystems &);
Q_GUI_EXPORT bool operator!=(const QSupportedWritingSystems &, const QSupportedWritingSystems &);

class QFontRequestPrivate;
class QFontEngineMulti;

class Q_GUI_EXPORT QPlatformFontDatabase
{
public:
    virtual ~QPlatformFontDatabase();
    virtual void populateFontDatabase();
    virtual void populateFamily(const QString &familyName);
    virtual void invalidate();

    virtual QFontEngineMulti *fontEngineMulti(QFontEngine *fontEngine, QChar::Script script);
    virtual QFontEngine *fontEngine(const QFontDef &fontDef, void *handle);
    virtual QStringList fallbacksForFamily(const QString &family, QFont::Style style, QFont::StyleHint styleHint, QChar::Script script) const;
    virtual QStringList addApplicationFont(const QByteArray &fontData, const QString &fileName);
    virtual void releaseHandle(void *handle);

    virtual QFontEngine *fontEngine(const QByteArray &fontData, qreal pixelSize, QFont::HintingPreference hintingPreference);

    virtual QString fontDir() const;

    virtual QFont defaultFont() const;
    virtual bool isPrivateFontFamily(const QString &family) const;

    virtual QString resolveFontFamilyAlias(const QString &family) const;
    virtual bool fontsAlwaysScalable() const;
    virtual QList<int> standardSizes() const;
    QFontEngine::SubpixelAntialiasingType subpixelAntialiasingTypeHint() const;

    // helper
    static QSupportedWritingSystems writingSystemsFromTrueTypeBits(quint32 unicodeRange[4], quint32 codePageRange[2]);
    static QFont::Weight weightFromInteger(int weight);

    //callback
    static void registerQPF2Font(const QByteArray &dataArray, void *handle);
    static void registerFont(const QString &familyname, const QString &stylename,
                             const QString &foundryname, QFont::Weight weight,
                             QFont::Style style, QFont::Stretch stretch, bool antialiased,
                             bool scalable, int pixelSize, bool fixedPitch,
                             const QSupportedWritingSystems &writingSystems, void *handle);

    static void registerFontFamily(const QString &familyName);
    static void registerAliasToFontFamily(const QString &familyName, const QString &alias);
};

QT_END_NAMESPACE

#endif // QPLATFORMFONTDATABASE_H
