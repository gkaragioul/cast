#ifdef OBS_AMD_LITE

#include "update-lite-amd.hpp"

#include <QByteArray>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QTextBrowser>
#include <QVBoxLayout>

#ifdef _WIN32
#include <windows.h>
#pragma comment(lib, "version.lib")

static QString GetAMFRuntimeVersion()
{
	const char *dllName = "amfrt64.dll";
	DWORD handle = 0;
	DWORD size = GetFileVersionInfoSizeA(dllName, &handle);
	if (size == 0)
		return QString();

	QByteArray buf(static_cast<int>(size), 0);
	if (!GetFileVersionInfoA(dllName, handle, size, buf.data()))
		return QString();

	VS_FIXEDFILEINFO *info = nullptr;
	UINT infoSize = 0;
	if (!VerQueryValueA(buf.constData(), "\\", reinterpret_cast<LPVOID *>(&info), &infoSize) || !info)
		return QString();

	return QStringLiteral("%1.%2.%3.%4")
		.arg(HIWORD(info->dwFileVersionMS))
		.arg(LOWORD(info->dwFileVersionMS))
		.arg(HIWORD(info->dwFileVersionLS))
		.arg(LOWORD(info->dwFileVersionLS));
}
#else
static QString GetAMFRuntimeVersion()
{
	return QString();
}
#endif

GKAboutDialog::GKAboutDialog(QWidget *parent) : QDialog(parent)
{
	setWindowTitle("About RDNA Cast");
	setFixedSize(480, 420);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	auto *layout = new QVBoxLayout(this);

	QString amfVersion = GetAMFRuntimeVersion();
	QString amfLine = amfVersion.isEmpty()
				  ? QStringLiteral("<p><b>AMD AMF runtime:</b> not detected</p>")
				  : QStringLiteral("<p><b>AMD AMF runtime:</b> %1</p>").arg(amfVersion);

	QString titleHtml = QStringLiteral(
				    "<div style='text-align:center;'>"
				    "<h1 style='color:#e63946;'>RDNA Cast</h1>"
				    "<p style='font-size:14px;'>Version " GK_OBS_LITE_VERSION " (64-bit)</p>"
				    "<p>High-performance streaming for AMD Radeon. Gaming unleashed.</p>"
				    "<p><b>Developer:</b> George Karagioules</p>"
				    "<p><b>Based on:</b> OBS Studio 31.0.3 by the OBS Project</p>") +
			    amfLine +
			    QStringLiteral(
				    "<p style='font-size:11px;color:#888;'>Not affiliated with, endorsed by, or sponsored by "
				    "Advanced Micro Devices, Inc. or the OBS Project. &quot;AMD&quot;, &quot;Radeon&quot;, and "
				    "&quot;RDNA&quot; are trademarks of Advanced Micro Devices, Inc.</p>"
				    "<hr>"
				    "</div>");

	auto *titleLabel = new QLabel(titleHtml);
	titleLabel->setWordWrap(true);
	titleLabel->setAlignment(Qt::AlignCenter);
	layout->addWidget(titleLabel);

	auto *eulaLabel = new QLabel("<b>Licenses</b>");
	layout->addWidget(eulaLabel);

	auto *eulaBrowser = new QTextBrowser();
	eulaBrowser->setPlainText(
		"RDNA Cast is free software, based on OBS Studio.\n\n"
		"It is licensed under the GNU General Public License, version 2 or "
		"(at your option) any later version (GPL-2.0-or-later), the same "
		"licence as OBS Studio. You may use, copy, change and share it under "
		"those terms. The full licence text is in the COPYING file installed "
		"next to the app.\n\n"
		"The complete source code for this version is available at:\n"
		"https://github.com/gkaragioul/cast\n\n"
		"Third-party components keep their own licences. See "
		"THIRD_PARTY_LICENSES.md installed next to the app.\n\n"
		"OBS Studio: Copyright (C) Hugh Bailey and contributors.\n"
		"RDNA Cast changes: Copyright (C) 2026 George Karagioules.\n"
		"AMD AMF SDK: Copyright (c) Advanced Micro Devices, Inc. (MIT licence).\n\n"
		"The names RDNA Cast and SiliconCast and their logos are not covered "
		"by the GPL. See TRADEMARKS.md.\n\n"
		"This program comes with ABSOLUTELY NO WARRANTY.\n\n"
		"Releases: " GK_OBS_LITE_RELEASES_URL);
	eulaBrowser->setReadOnly(true);
	layout->addWidget(eulaBrowser);

	auto *closeButton = new QPushButton("Close");
	closeButton->setDefault(true);

	auto *btnLayout = new QHBoxLayout();
	btnLayout->addStretch();
	btnLayout->addWidget(closeButton);
	layout->addLayout(btnLayout);

	connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
}

#endif /* OBS_AMD_LITE */
