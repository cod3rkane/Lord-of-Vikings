#include <iostream>
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <gtk/gtk.h>
// #include <GLFW/glfw3.h>
#include "util/ProjectionMatrix.h"
#include "util/Shader.h"
#include "GlModel.h"
#include "legacy/Camera.h"
#include "legacy/Entity.h"

#define OPENGL_MAJOR 4
#define OPENGL_MINOR 5

static void on_realize(GtkGLArea *glarea) {
	// Make current:
	gtk_gl_area_make_current(glarea);

	// Init GLEW:
	glewExperimental = GL_TRUE;
	glewInit();

	// Enable depth buffer:
	gtk_gl_area_set_has_depth_buffer(glarea, TRUE);

	// Get frame clock:
    GdkGLContext *glcontext = gtk_gl_area_get_context(glarea);
	GdkWindow *glwindow = gdk_gl_context_get_window(glcontext);
    GdkFrameClock *frame_clock = gdk_window_get_frame_clock(glwindow);

    // Print version info:
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	// Connect update signal:
	g_signal_connect_swapped(frame_clock, "update", G_CALLBACK(gtk_gl_area_queue_render), glarea);

	// Start updating:
	gdk_frame_clock_begin_updating(frame_clock);
}

static gboolean on_render(GtkGLArea *glarea, GdkGLContext *context) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Don't propagate signal:
	return TRUE;
}

static void on_resize(GtkGLArea *area, gint width, gint height) {
    std::cout << "Window Resized" << std::endl;
}

static void connect_window_signals(GtkWidget *window) {
    gtk_widget_add_events(window, 0);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

static GdkGLContext* creating_context(GtkGLArea *glarea) {
    // render things...
    GError* err = nullptr;

    GdkWindow *window = gtk_widget_get_window(glarea);
    GdkGLContext *context = gdk_window_create_gl_context(window, &err);

    return context;
}

static void connect_glarea_signals(GtkWidget *glarea) {
    gtk_widget_add_events(glarea, 0);
    g_signal_connect(glarea, "create-context", G_CALLBACK(creating_context), NULL);

    gtk_widget_add_events(glarea, 0);
    g_signal_connect(glarea, "realize", G_CALLBACK(on_realize), NULL);

    gtk_widget_add_events(glarea, 0);
    g_signal_connect(glarea, "render", G_CALLBACK(on_render), NULL);

    gtk_widget_add_events(glarea, 0);
    g_signal_connect(glarea, "resize", G_CALLBACK(on_resize), NULL);
}

int main(int argc, char* argv[]) {
    // Initialize GTK+
    if(!gtk_init_check(&argc, &argv)) {
        std::cout << "Could'nt initialize GTK" << std::endl;
    }

    // Create toplevel window, add GtkGLArea:
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *glarea = gtk_gl_area_new();
	gtk_container_add(GTK_CONTAINER(window), glarea);

	// Connect GTK signals:
	connect_window_signals(window);
	connect_glarea_signals(glarea);

	gtk_widget_show_all(window);

	// Enter GTK event loop:
	gtk_main();

	return true;
    return EXIT_SUCCESS;
}
