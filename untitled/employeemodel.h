#ifndef EMPLOYEEMODEL_H
#define EMPLOYEEMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class EmployeeItem {
public:
    explicit EmployeeItem(const QString &name, const int &cppVal, const int &qmlVal, const int &openGlVal, const int &jsVal, const int &avgVal) {
        pName = name;
        pCppVal = cppVal;
        pQmlVal = qmlVal;
        pOpenGlVal = openGlVal;
        pJsVal = jsVal;
        pAvgVal = avgVal;
    };

    QString name() const {
        return pName;
    }

    int cppVal() const{
        return pCppVal;
    }

    int qmlVal() const{
        return pQmlVal;
    }

    int openGlVal() const{
        return pOpenGlVal;
    }

    int jsVal() const{
        return pJsVal;
    }

    int avgVal() const{
        return pAvgVal;
    }

    bool setName(const QString &name) {
        if(pName == name) {
            return false;
        }

        pName = name;
        return true;
    }

    bool setCppVal(const int &cppVal) {
        if(pCppVal == cppVal) {
            return false;
        }

        pCppVal = cppVal;
        return true;
    }

    bool setQmlVal(const int &qmlVal) {
        if(pQmlVal == qmlVal) {
            return false;
        }

        pQmlVal = qmlVal;
        return true;
    }

    bool setOpenGlVal(const int &openGlVal) {
        if(pOpenGlVal == openGlVal) {
            return false;
        }

        pOpenGlVal = openGlVal;
        return true;
    }

    bool setJsVal(const int &jsVal) {
        if(pJsVal == jsVal) {
            return false;
        }

        pJsVal = jsVal;
        return true;
    }

    bool setAvgVal(const int &avgVal) {
        if(pAvgVal == avgVal) {
            return false;
        }

        pAvgVal = avgVal;
        return true;
    }
private:
    QString pName;
    int pCppVal;
    int pQmlVal;
    int pOpenGlVal;
    int pJsVal;
    bool pAvgVal;
};

class EmployeeModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString inputFile READ inputFile WRITE setInputFile NOTIFY inputFileChanged)

signals:
    void inputFileChanged();
public:
    QString inputFile() const {
        return pInputFile;
    }

    void setInputFile(QString const &inputFile) {
        if(pInputFile == inputFile) {
            return;
        }

        pInputFile = inputFile;
        loadEmployeeListModelFromInputFile();
        emit inputFileChanged();
    }
    EmployeeModel(QObject *parent = nullptr) : QAbstractListModel(parent) {
    }

    enum EmployeeItemRoles {
        NameRole = Qt::UserRole+1,
        CppValRole,
        QmlValRole,
        OpenGlValRole,
        JsValRole,
        AvgValRole,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return pEmployeeList.length();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if(!index.isValid()) {
            return QVariant();
        }

        const EmployeeItem &item = pEmployeeList[index.row()];

        switch (role) {
        case NameRole:
            return item.name();
        case CppValRole:
            return item.cppVal();
        case QmlValRole:
            return item.qmlVal();
        case OpenGlValRole:
            return item.openGlVal();
        case JsValRole:
            return item.jsVal();
        case AvgValRole:
            return item.avgVal();
        default:
            return QVariant();
        }
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override {
        if(!index.isValid()) {
            return false;
        }

        EmployeeItem &item = pEmployeeList[index.row()];

        switch (role) {
        case NameRole:
            return item.setName(value.toString());
        case CppValRole:
            return item.setJsVal(value.toInt());
        case QmlValRole:
            return item.setOpenGlVal(value.toInt());
        case OpenGlValRole:
            return item.setOpenGlVal(value.toInt());
        case JsValRole:
            return item.setJsVal(value.toInt());
        case AvgValRole:
            return item.setAvgVal(value.toInt());
        default:
            return false;
        }
    }

    Q_INVOKABLE void saveEmployeeListModelToFile() {
        QFile saveDoc(pInputFile);

        if(!saveDoc.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            qWarning("Could not open file!");
            return;
        }

        QJsonObject rootObject;
        QJsonArray employeeListArray;

        for(int index = 0; index < pEmployeeList.size(); index++) {
            QJsonObject employeeItemJson;
            employeeItemJson["name"] = pEmployeeList[index].name();
            employeeItemJson["cppVal"] = pEmployeeList[index].cppVal();
            employeeItemJson["qmlVal"] = pEmployeeList[index].qmlVal();
            employeeItemJson["openGlVal"] = pEmployeeList[index].openGlVal();
            employeeItemJson["jsVal"] = pEmployeeList[index].jsVal();
            employeeItemJson["avgVal"] = pEmployeeList[index].avgVal();
            employeeListArray.append(employeeItemJson);
        }

        rootObject["employeeList"] = employeeListArray;

        auto writeContent = QJsonDocument(rootObject).toJson();

        saveDoc.write(writeContent);
        saveDoc.close();
    }
protected:
    QHash<int, QByteArray> roleNames() const override{
        QHash<int, QByteArray> roles;
        roles[NameRole] = "name";
        roles[CppValRole] = "cppVal";
        roles[QmlValRole] = "qmlVal";
        roles[OpenGlValRole] = "openGlVal";
        roles[JsValRole] = "jsVal";
        roles[AvgValRole] = "avgVal";
        return roles;
    }

private:
    QList<EmployeeItem> pEmployeeList;
    QString pInputFile;

    void loadEmployeeListModelFromInputFile() {
        QFile loadDoc(pInputFile);

        if(!loadDoc.open(QIODevice::ReadOnly)) {
            qWarning("Could not open file!");
            return;
        }

        auto fileContent = loadDoc.readAll();

        QJsonDocument saveFileDoc = QJsonDocument::fromJson(fileContent);

        QJsonObject rootObject = saveFileDoc.object();

        if(rootObject.contains("employeeList") && rootObject["employeeList"].isArray()) {
            auto employeeListJsonArray = rootObject["employeeList"].toArray();
            QList<EmployeeItem> newEmployeeList;
            for(int index = 0; index < employeeListJsonArray.size(); index++) {
                auto jsonEmployeeItem = employeeListJsonArray[index].toObject();
                auto newEmployeeItem = EmployeeItem(jsonEmployeeItem["name"].toString(),
                                                    jsonEmployeeItem["cppVal"].toInt(),
                                                    jsonEmployeeItem["qmlVal"].toInt(),
                                                    jsonEmployeeItem["openGlVal"].toInt(),
                                                    jsonEmployeeItem["jsVal"].toInt(),
                                                    jsonEmployeeItem["avgVal"].toInt());
                newEmployeeList.append(newEmployeeItem);
            }

            beginResetModel();
            pEmployeeList = newEmployeeList;
            endResetModel();
            loadDoc.close();
        }else {
            qWarning("file not contain todolist key");
            return;
        }
    }
};

#endif // EMPLOYEEMODEL_H
