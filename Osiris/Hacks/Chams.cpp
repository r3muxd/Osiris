#include <fstream>

#include "../xorstr.hpp"

#include "Chams.h"
#include "../Config.h"
#include "../Interfaces.h"
#include "../Memory.h"

void Chams::render()
{
    if (config.chams.enabled) {
        for (int i = 1; i < interfaces.engineClient->GetMaxClients(); ++i) {
            BaseEntity* entity = interfaces.clientEntityList->getClientEntity(i);

            if (entity && entity->isAlive()) {
                interfaces.renderView->setBlend(config.chams.alpha);
                if (entity->getTeamNumber() != (*memory.localPlayer)->getTeamNumber())
                    interfaces.renderView->setColorModulation(config.chams.enemiesColor);
                else if (config.chams.enemiesOnly)
                    continue;
                else
                    interfaces.renderView->setColorModulation(config.chams.alliesColor);

                auto material = interfaces.materialSystem->findMaterial(xorstr_("dev/glow_color"), nullptr);
                if (material) {
                    material->setMaterialVarFlag(MaterialVar::WIREFRAME, config.chams.wireframe);
                    interfaces.modelRender->forceMaterialOverride(material);
                    entity->drawModel(1, 255);
                    interfaces.modelRender->forceMaterialOverride(nullptr);
                    material->setMaterialVarFlag(MaterialVar::WIREFRAME, false);
                }
            }
        }
    }
}
