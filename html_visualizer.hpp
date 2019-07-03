#pragma once
#ifndef INCLUDE_HTML_VISUALIZER_HPP__
#define INCLUDE_HTML_VISUALIZER_HPP__

#include <cstdio>
#include <cstdlib>

namespace HtmlVisualizer {

using namespace std;

namespace VisConstants {

const char *html_head =
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

const char *html_tail =
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

class Vis {
private:
    FILE *fp;
    int page_count = 1;

    void set_color(Color c) {
        fprintf(fp, "ctx.fillStyle=\"rgb(%d,%d,%d)\";", c.r, c.g, c.b);
        fprintf(fp, "ctx.stokeStyle=\"rgb(%d,%d,%d)\";", c.r, c.g, c.b);
    }

public:
    Vis(string filename = "result.html") {
        fp = fopen(filename.c_str(), "w");
        fprintf(fp, "%s", VisConstants::html_head);
    }

    ~Vis() {
        fprintf(fp, "}\nconst page_func=[page1");
        for(int i = 2; i <= page_count; ++i) {
            fprintf(fp, ",page%d", i);
        }
        fprintf(fp, "];");
        fprintf(fp, "%s\n", VisConstants::html_tail);
        fclose(fp);
    }

    void new_page() {
        page_count++;
        fprintf(fp, "}\nfunction page%d(ctx){", page_count);
    }

    void circle(double x, double y, double radius, Color bg = {0, 0, 0}) {
        set_color(bg);
        fprintf(fp,
            "ctx.beginPath();"
            "ctx.arc(%.2lf,%.2lf,%.2lf,0,Math.PI*2,false);"
            "ctx.closePath();"
            "ctx.fill();",
            x, y, radius
        );
    }

    void rect(double x, double y, double w, double h, Color bg = {0, 0, 0}, bool border = false) {
        set_color(bg);
        fprintf(fp,
            "ctx.fillRect(%.2lf,%.2lf,%.2lf,%.2lf);",
            x, y, w, h
        );
        if(border) {
            fprintf(fp,
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
