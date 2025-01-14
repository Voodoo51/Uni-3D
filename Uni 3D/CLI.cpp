#include "CLI.h"

CLI cli;

void HelpC(std::vector<char*> words)
{
    for (int i = 0; i < cli.commands.size(); i++)
        cli.AddLog(cli.commands[i].signature);
}

void CreateC(std::vector<char*> words)
{
    for (int i = 0; i < words.size(); i++)
        std::cout << words[i] << std::endl;

    if (words.size() < 3)
    {
        cli.AddLog("Za malo argumentow.");
        return;
    }

    for (int i = 0; i < strlen(words[1]); i++)
    {
        if (!isdigit(*(words[1] + i)))
        {
            cli.AddLog("Pierwszy argument musi byc liczba.");
            return;
        }
    }

    for (int i = 0; i < strlen(words[2]); i++)
    {
        if (!isdigit(*(words[2] + i)))
        {
            cli.AddLog("Drugi argument musi byc liczba.");
            return;
        }
    }

    if (atoi(words[1]) <= 0 || atoi(words[2]) <= 0)
    {
        cli.AddLog("Argument nie moze byc rowny badz mniejszy od 0.");
        return;
    }

    int x = atoi(words[1]);
    int y = atoi(words[2]);
    std::cout << "X: " << x << " Y: " << y << std::endl;
    map.GenerateMap(x, y);
}

void SetShadingC(std::vector<char*> words)
{
    if (words.size() < 2)
    {
        cli.AddLog("Brak argumentu.");
        return;
    }

    char* word = words[1];

    if (strcmp(word, "blinnphong") == 0)
    {
        cli.AddLog("Zmiana cieniowania na BlinnPhong");
        renderer.ChangeShading(BlinnPhong);
        return;
    }
    if (strcmp(word, "gourard") == 0)
    {
        cli.AddLog("Zmiana cieniowania na Gourard");
        renderer.ChangeShading(Gourard);
        return;
    }
    if (strcmp(word, "flat") == 0)
    {
        cli.AddLog("Zmiana cieniowania na flat");
        renderer.ChangeShading(Flat);
        return;
    }

    cli.AddLog("Nie ma takiej opcji");
    return;
}

void CLI::Init()
{
    commands.push_back({ "help", HelpC });
    commands.push_back({ "create", CreateC });
    commands.push_back({ "set_shading", SetShadingC });
}

void CLI::Draw(ImGuiIO& io)
{
    static float f = 0.0f;
	static int counter = 0;
		
	ImGui::Begin("Konsola");                          // Create a window called "Hello, world!" and append into it.
    char text[120] = {0};
	ImGui::InputText("Text", text, IM_ARRAYSIZE(text));
    ImGui::Separator();// Display some text (you can use a format strings too)
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing

    for (const char* item : items)
    {
        ImVec4 color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f);
        bool has_color = false;
        ImGui::TextUnformatted(item);
    }
    
    if (input.KeyPressedOnce(SDLK_RETURN))
    {
        AddLog(text);
        Parse();
    }

    ImGui::PopStyleVar();
	ImGui::End();
}

static char* Strdup(const char* s) { IM_ASSERT(s); size_t len = strlen(s) + 1; void* buf = ImGui::MemAlloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)s, len); }

void CLI::AddLog(const char* fmt, ...) IM_FMTARGS(2)
{
    // FIXME-OPT
    char buf[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
    buf[IM_ARRAYSIZE(buf) - 1] = 0;
    va_end(args);
    items.push_back(Strdup(buf));
}

void CLI::Parse()
{
    const char* itemData = items[items.size() - 1];
    int stringLength = strlen(itemData);

    char *item = (char *)malloc(sizeof(char) * stringLength);
    for (int i = 0; i < stringLength; i++)
    {
          item[i] = itemData[i];
    }

    const char* delim = " ";
    char* context = NULL;
    char* nextToken = NULL;

    std::vector<char*> words;

    nextToken = strtok_s(item, delim, &context);

    while (nextToken != NULL)
    {
        words.push_back(nextToken);
        nextToken = strtok_s(NULL, delim, &context);
    }

    if (words.size() == 0) return;

    for (int i = 0; i < commands.size(); i++)
    {
        if (strcmp(words[0], commands[i].signature) == 0)
        {
            commands[i].Func(words);
            return;
        }
    }

    AddLog("Nie ma takiej komendy.");
}
