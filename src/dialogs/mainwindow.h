///
/// \file
/// This file contains the main window declaration.
///

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QTableWidget>
#include <QSignalMapper>
#include <QTranslator>
#include <QCloseEvent>
#include "apkmanager.h"
#include "combolist.h"
#include "drawarea.h"
#include "effectsdialog.h"
#include "tooldialog.h"
#include "keymanager.h"
#include "dialogs.h"
#include "about.h"
#include "updater.h"
#include "recent.h"
#include "cloud.h"

///
/// Main window class.
/// This class describes the main "APK Icon Editor" window.
///

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    void init_core();      ///< Initializes base objects.
    void init_gui();       ///< Initializes windows and widgets.
    void init_languages(); ///< Initializes available languages.
    void init_devices();   ///< Initializes available device presets.
    void init_slots();     ///< Initializes signals/slots.

    void checkReqs();      ///< Checks Java and Apktool versions.
    bool resetApktool();   ///< Removes the Apktool "1.apk" framework file.
    bool confirmExit();    ///< Displays the exit confirmation dialog.
    void invalidDpi();     ///< Displays the "Invalid DPI" message.

    /// Marks the specified \c filename as currently active.
    void setActiveApk(QString filename);

    /// Uploads the specified file to a cloud service.
    /// \param uploader Cloud uploader object.
    /// \param filename Name of the file to upload.
    void upload(Cloud *uploader, QString filename);

    // Dialogs:

    About *about;
    EffectsDialog *effects;
    ToolDialog *toolDialog;
    KeyManager *keyManager;
    ProgressDialog *loadingDialog;
    ProgressDialog *uploadDialog;

    // Widgets:

    QSplitter *splitter;
    DrawArea *drawArea;
    QTabWidget *tabs;
    ComboList *devices;
    QPushButton *btnApplyIcons;
    QLabel *labelTool;
    QToolButton *btnTool;
    QLabel *labelAppName;
    QLabel *labelVersionName;
    QLabel *labelVersionCode;
    QLineEdit *editAppName;
    QLineEdit *editVersionName;
    QSpinBox *editVersionCode;
    QPushButton *btnApplyAppName;
    QWidget *panelApktool;
    QLabel *labelApktool;
    QPushButton *btnRepacking;
    QTableWidget *tableStrings;
    QCheckBox *checkDropbox;
    QCheckBox *checkGDrive;
    QCheckBox *checkOneDrive;
    QCheckBox *checkUpload;
    QPushButton *btnPack;

    // Menus:

    QMenu *menuFile;
    QMenu *menuIcon;
    QMenu *menuSett;
    QMenu *menuHelp;
    QMenu *menuRecent;
    QMenu *menuLang;
    QMenu *menuLogs;

    // Actions:

    QAction *actApkOpen;
    QAction *actApkExplore;
    QAction *actApkSave;
    QAction *actExit;
    QAction *actRecentClear;
    QAction *actNoRecent;
    QAction *actIconOpen;
    QAction *actIconSave;
    QAction *actIconScale;
    QAction *actIconResize;
    QAction *actIconRevert;
    QAction *actIconBack;
    QAction *actIconEffect;
    QAction *actPacking;
    QAction *actKeys;
    QAction *actTranslate;
    QAction *actAssoc;
    QAction *actReset;
    QAction *actAutoUpdate;
    QAction *actFaq;
    QAction *actWebsite;
    QAction *actReport;
    QAction *actDonate;
    QAction *actLogFile;
    QAction *actLogPath;
    QAction *actUpdate;
    QAction *actAboutQt;
    QAction *actAbout;

    // Base:

    Apk::File *apk;
    ApkManager *apkManager;
    Recent *recent;
    Updater *updater;
    Dropbox *dropbox;
    GoogleDrive *gdrive;
    OneDrive *onedrive;

    // Other:

    QSignalMapper *mapLang;
    QSignalMapper *mapRecent;
    QTranslator *translator;
    QTranslator *translatorQt;
    QString currentApk;
    QString currentLang;
    QString currentPath;

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);
    void closeEvent(QCloseEvent *event);

public slots:
    /// Opens APK located with the specified \c filename.
    /// Displays the "Open APK" dialog if the \c filename is not specified.
    bool apk_open(QString filename = QString());

    /// Saves APK to the specified \c filename.
    /// Displays the "Save APK" dialog if the \c filename is not specified.
    bool apk_save(QString filename = QString());

    /// Opens the directory containing the unpacked APK files.
    void apk_explore();

signals:
    /// This signal is emmitted after the Java and Apktool versions check was performed.
    void reqsChecked(QString jre, QString jdk, QString apktool);

private slots:

    // APK:

    /// Handles the packed APK.
    /// \param apk       Object representing the packed APK.
    /// \param text      Additional message text.
    /// \param isSuccess Contains \c false if the APK is packed with warnings.
    void apkPacked(Apk::File *apk, QString text = QString(), bool isSuccess = true);

    /// Handles the unpacked APK.
    /// \param apk Object representing the unpacked APK.
    void apkUnpacked(Apk::File *apk);

    // Settings:

    void settings_load();  ///< Loads application settings from INI.
    void settings_reset(); ///< Resets application settings to default.

    // Icons:

    /// Loads icon from the file with the given \c filename.
    /// Displays the "Open Icon" dialog if the \c filename is not specified.
    bool iconOpen(QString filename = QString());

    /// Saves the current icon to the file with the specified \c filename.
    /// Displays the "Save Icon" dialog if the \c filename is not specified.
    bool iconSave(QString filename = QString());

    /// Resizes the current icon to a square with the specified \c side.
    /// \param side New side value in pixels. If zero, asks user for a value.
    /// Displays the "Save Icon" dialog if the \c filename is not specified.
    bool iconResize(int side = 0);

    /// Scales the current icon to the appropriate size.
    bool iconScale();

    /// Reverts the original APK icon.
    bool iconRevert();

    // Recent:

    void recent_add(QString filename); ///< Adds the specified \c filename to the recent list.
    void recent_update();              ///< Updates the recent menu.
    void recent_clear();               ///< Clears the list of recently opened APK files.

    // Actions:

    void associate() const;          ///< Sets "APK Icon Editor" as the default application for \c apk files (Windows only).
    void browseSite() const;         ///< Opens website URL in the default browser.
    void browseBugs() const;         ///< Opens bugs webpage in the default browser.
    void browseTranslate();          ///< Opens Transifex URL in the default browser.
    void browseFaq() const;          ///< Opens FAQ text document.
    void openLogFile() const;        ///< Opens log file.
    void openLogPath() const;        ///< Opens log directory.

    void setLanguage(QString lang);  ///< Sets GUI language to \c lang.
    void setCurrentIcon(int id);     ///< Displays the icon with the specified DPI \c id in the icon preview widget.
    void setModified();              ///< Marks the current APK as containing unsaved changes.
    void hideEmptyDpi();             ///< Hides empty icons from the list.
    void cloneIcons();               ///< Clones the current icon for to all sizes.
    void stringChanged(int, int);    ///< Handles the changes in the strings table.
    void applyAppName();             ///< Applies the global application name to all translations.
    void enableUpload(bool enable);  ///< Enables or disables upload to cloud services.
    void enableApktool(bool enable); ///< Enables or disables editing of the application name/version.

    // Dialogs:

    void donate();            ///< Displays donation dialog.
    void authCloud();         ///< Displays cloud authentication input dialog.
    void askReloadApk();      ///< Displays the "Repack APK?" question dialog.
    bool setPreviewColor();   ///< Displays background color selection dialog.
    void showEffectsDialog(); ///< Displays "Effects" dialog.

    /// Displays the "New version available" dialog.
    /// \param version Number representing the new version.
    bool newVersion(QString version);

    /// Displays success message.
    /// \param title Message brief title.
    /// \param text  Message detailed text.
    void success(QString title, QString text);

    /// Displays warning message.
    /// \param title Message brief title.
    /// \param text  Message detailed text.
    void warning(QString title, QString text);

    /// Displays error message.
    /// \param title Message brief title.
    /// \param text  Message detailed text.
    void error(QString title, QString text);

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
