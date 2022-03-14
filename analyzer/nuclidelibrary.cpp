#include "nuclidelibrary.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

namespace model {

NuclideLibrary::NuclideLibrary()
{
    QFile jsonFile("nuclidelibrary.json");
    jsonFile.open(QFile::ReadOnly);
    auto jsonObject = QJsonDocument().fromJson(jsonFile.readAll()).object();

    int id = 0;
    for (auto it = jsonObject.begin(); it != jsonObject.end(); it++) {
        nuclide_t nuclide;
        nuclide.name = it.key().toStdString();
        assert(it->isObject());
        auto subObject = it->toObject();
        assert(subObject.contains("color"));
        assert(subObject.contains("lines"));
        assert(subObject["lines"].isArray());
        nuclide.color = subObject["color"].toInt();
        auto linesArray = subObject["lines"].toArray();
        for (const auto &pair : qAsConst(linesArray)) {
            assert(pair.isArray());
            assert(pair.toArray().size() == 2);
            nuclide.lines.push_back(
                        {
                            pair.toArray().at(0).toDouble(),
                            pair.toArray().at(1).toDouble()
                        }
                        );
        }
        m_library[id++] = nuclide;
    }
}

nuclides_t NuclideLibrary::nuclides([[maybe_unused]]const probas_t &probas)
{
    nuclides_t result{m_library[4], m_library[8]};
    return result;
}

}
