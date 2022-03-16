#include "nuclidelibrary.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

namespace model {

NuclideLibraryPtr NuclideLibrary::m_instance = nullptr;


NuclideLibraryPtr NuclideLibrary::instance(const std::string &filename)
{
    if (m_instance == nullptr) {
        m_instance = NuclideLibraryPtr{new NuclideLibrary(filename)};
    }
    return m_instance;
}

NuclideLibrary::NuclideLibrary(const std::string &filename)
{
    QFile jsonFile(filename.c_str());
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

nuclides_t NuclideLibrary::nuclidesAll() const
{
    nuclides_t result(m_library.size());
    auto idx = 0;
    for (const auto &node : m_library) {
        result[idx++] = node.second;
    }
    return result;
}

std::vector<std::string> NuclideLibrary::nuclideNames() const
{
    std::vector<std::string> result;
    for (const auto &node : m_library) {
        result.push_back(node.second.name);
    }
    return result;
}

size_t NuclideLibrary::numClasses() const
{
    return m_library.size();
}

nuclides_t NuclideLibrary::nuclides([[maybe_unused]]const probas_t &probas) const
{
    qDebug() << probas;
    nuclides_t result;
    for (auto i = 0u; i < probas.size(); i++) {
        if (probas[i] > 0.2) {
            result.push_back(m_library.at(i));
            result.back().activity = probas[i];
        }
    }
    return result;
}

}
