#pragma once
#ifndef INCLUDE_HTML_VISUALIZER_HPP__
#define INCLUDE_HTML_VISUALIZER_HPP__

#include <string>
#include <cstdio>

namespace HtmlVisualizer {

namespace VisConstants {

const char *HTML_HEAD =
"<html><head><script type=\"text/javascript\">"
"var now_page = 0;"
"function draw() {"
    "var cv = document.getElementById(\"c\");"
    "var ctx = cv.getContext(\"2d\");"
    "ctx.fillStyle = \"#fff\";"
    "ctx.fillRect(0, 0, 800, 800);"
    "page_func[now_page](ctx);"
"}"

"onload = draw;"

"function next_page() {"
    "if(now_page + 1 < page_func.length) {"
        "now_page += 1;"
    "}"
    "draw();"
"}"

"function prev_page() {"
    "if(0 < now_page) {"
        "now_page -= 1;"
    "}"
    "draw();"
"}\n"

"function page1(ctx) {";

const char *HTML_TAIL =
"</script></head><body>"
"<input type=\"button\" value=\"prev\" onclick=\"prev_page();\"></input>"
"<input type=\"button\" value=\"next\" onclick=\"next_page();\"></input>"
"<br/>"
"<canvas id=\"c\" width=\"800\" height=\"800\"></canvas>"
"</body></html>";

} // namespace: VisConstants

struct Color {
    int r, g, b;
};

namespace Palette {
    constexpr Color Black = {0, 0, 0};
    constexpr Color White = {255, 255, 255};
    constexpr Color Gray = {150, 150, 150};
    constexpr Color Purple = {97, 68, 208};
    constexpr Color Blue = {83, 146, 210};
    constexpr Color Green = {100, 216, 127};
    constexpr Color Yellow = {248, 232, 70};
    constexpr Color Orange = {232, 140, 84};
    constexpr Color Red = {223, 71, 87};
} // namespace: Palette

class Vis {
private:
    FILE *fp;
    int page_count = 1;

    void set_color(Color c) {
        std::fprintf(fp, "ctx.fillStyle=\"rgb(%d,%d,%d)\";", c.r, c.g, c.b);
        std::fprintf(fp, "ctx.stokeStyle=\"rgb(%d,%d,%d)\";", c.r, c.g, c.b);
    }

public:
    Vis(std::string filename = "result.html") {
        fp = std::fopen(filename.c_str(), "w");
        std::fprintf(fp, "%s", VisConstants::HTML_HEAD);
    }

    ~Vis() {
        std::fprintf(fp, "}\nconst page_func=[page1");
        for(int i = 2; i <= page_count; ++i) {
            std::fprintf(fp, ",page%d", i);
        }
        std::fprintf(fp, "];");
        std::fprintf(fp, "%s\n", VisConstants::HTML_TAIL);
        std::fclose(fp);
    }

    void new_page() {
        page_count++;
        std::fprintf(fp, "}\nfunction page%d(ctx){", page_count);
    }

    void circle(double x, double y, double radius, Color bg = {0, 0, 0}) {
        set_color(bg);
        std::fprintf(fp,
            "ctx.beginPath();"
            "ctx.arc(%.2lf,%.2lf,%.2lf,0,Math.PI*2,false);"
            "ctx.closePath();"
            "ctx.fill();",
            x, y, radius
        );
    }

    void rect(double x, double y, double w, double h, Color bg = {0, 0, 0}, bool border = false) {
        set_color(bg);
        std::fprintf(fp,
            "ctx.fillRect(%.2lf,%.2lf,%.2lf,%.2lf);",
            x, y, w, h
        );
        if(border) {
            std::fprintf(fp,
                "ctx.stokeStyle=\"rgb(0,0,0)\";"
                "ctx.rect(%.2lf,%.2lf,%.2lf,%.2lf);"
                "ctx.stroke();",
                x, y, w, h
            );
        }
    }
};

} // namespace: HtmlVisualizer

#endif
