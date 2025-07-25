#include "App.h"

namespace GGE
{

    int32 GGE::RunApplication(std::shared_ptr<IApp> app)
    {
        GGE_ASSERT(app && "Failed to run empty application!");
        if (app) // just in case, for distribution ready build, manual check
        {
            GGE_ASSERT(app->Create() && "Failed to create app!");
            GGE_ASSERT(app->Run() && "IApp::Run() exited abnormally!");
            app->Destroy();
        }

        return 0;
    }

}
