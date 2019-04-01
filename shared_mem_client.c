#include <gtk/gtk.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

GtkWidget *window;
GtkWidget *button;
GtkWidget *button2;
GtkWidget *label;
GtkWidget *entry;
GtkWidget *vbox;
GtkWidget *hbox;

char *shmptr;

void button_copy_to_clicked(GtkWidget *window, gpointer data)
{
    const char* entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
    strcpy(shmptr, entry_text);
    gtk_label_set_text(GTK_LABEL(label), "write ok!");
}

void button2_copy_from_clicked(GtkWidget *window, gpointer data)
{
    char buf[256];
    strcpy(buf, shmptr);
    gtk_entry_set_text(GTK_ENTRY(entry), buf);
    gtk_label_set_text(GTK_LABEL(label), "read ok!");

}

int main(int argc, char *argv[])
{

    int shmid;
    if ((shmid = shmget((key_t)8989, 256, 0666)) < 0)
    {
        printf("shmget failed.\n");
        return 1;
    }
    if ((shmptr = shmat(shmid, 0, 0)) == -1)
    {
        printf("shmat failed.\n");
        shmctl(shmid, IPC_RMID, shmptr);
        return 2;
    }

    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 60);

    label = gtk_label_new("shared memory client");
    button = gtk_button_new_with_label("write shared memory");
    button2 = gtk_button_new_with_label("read shared memory");
    entry = gtk_entry_new();

    vbox = gtk_vbox_new(FALSE, 10);
    hbox = gtk_hbox_new(FALSE, 10);

    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), entry, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), button2, TRUE, FALSE, 5);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);

    gtk_signal_connect(GTK_OBJECT(window), "destory",
                       GTK_SIGNAL_FUNC(gtk_main_quit), NULL);
    gtk_signal_connect(GTK_OBJECT(button), "clicked",
                       GTK_SIGNAL_FUNC(button_copy_to_clicked), NULL);
    gtk_signal_connect(GTK_OBJECT(button2), "clicked",
                       GTK_SIGNAL_FUNC(button2_copy_from_clicked), NULL);
    gtk_main();
    return 0;
}
