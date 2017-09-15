import qbs 1.0

Project {
    name: "AppCenter"

    readonly property string version: "0.1.0"
    readonly property var versionParts: version.split('.').map(function(part) { return parseInt(part); })

    condition: qbs.targetOS.contains("linux")

    minimumQbsVersion: "1.8.0"

    references: [
        "app/app.qbs",
        "declarative/declarative.qbs",
        "framework/framework.qbs",
        "notifier/notifier.qbs",
    ]
}
