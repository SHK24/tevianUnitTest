#include <QtTest>
#include "../../tevianGUI/jsonparser.h"

// add necessary includes here

class jsonparser : public QObject
{
    Q_OBJECT

public:
    jsonparser();
    ~jsonparser();

private slots:
    void get_token_test();
    void get_face_box_test();
    void empty_data_test();
    void broken_field_test();
};

jsonparser::jsonparser()
{

}

jsonparser::~jsonparser()
{

}

void jsonparser::get_token_test()
{
    jsonParser parser;

    QFile jsonFile("../testdata/jsontest_token.txt");
    jsonFile.open(QIODevice::ReadOnly);

    QByteArray jsonData = jsonFile.readAll();

    QString token = parser.getToken(jsonData);

    QCOMPARE(token, "user_token");
}

void jsonparser::get_face_box_test()
{
    jsonParser parser;
    FaceDescription faceBox;

    QFile jsonFile("../testdata/jsontest_facebox.txt");
    jsonFile.open(QIODevice::ReadOnly);

    QByteArray jsonData = jsonFile.readAll();

    faceBox = parser.getFaceBox(jsonData);

    QCOMPARE(faceBox.x, 64);
    QCOMPARE(faceBox.y, 40);
    QCOMPARE(faceBox.width, 64);
    QCOMPARE(faceBox.height, 64);
    QCOMPARE(faceBox.age, 28);
}

void jsonparser::empty_data_test()
{
    jsonParser parser;
    FaceDescription faceBox;

    QByteArray jsonData;

    faceBox = parser.getFaceBox(jsonData);

    QCOMPARE(faceBox.status, false);
}

void jsonparser::broken_field_test()
{
    jsonParser parser;
    FaceDescription faceBox;

    QFile jsonFile("../testdata/jsontest_brokenField.txt");
    jsonFile.open(QIODevice::ReadOnly);

    QByteArray jsonData = jsonFile.readAll();

    faceBox = parser.getFaceBox(jsonData);

    QCOMPARE(faceBox.status, false);
}

QTEST_APPLESS_MAIN(jsonparser)

#include "tst_jsonparser.moc"
