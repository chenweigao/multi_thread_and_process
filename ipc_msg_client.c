#include <gtk/gtk.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 512

struct my_msg_st
{
	long int my_msg_type;
	char some_text[MAX_TEXT];
};


GtkWidget *window;
GtkWidget *button;
GtkWidget *label;
GtkWidget *entry;
GtkWidget *vbox;


void button_clicked(GtkWidget *widget, gpointer data)
{
	struct my_msg_st some_data;
	int msg_id;
	
	msg_id = msgget((key_t)1234, 0666|IPC_CREAT);
	if (msg_id == -1) {
		gtk_label_set_text(GTK_LABEL(label), "msgget failed.");
		return;
	}
	const char *entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
	some_data.my_msg_type = 1;
	strcpy(some_data.some_text, entry_text);
	if(msgsnd(msg_id, (void *)&some_data, MAX_TEXT, 0) == -1)
	{
		gtk_label_set_text(GTK_LABEL(label), "msgsnd failed,");
		return;
	}
	
}


int main(int argc, char *argv[])
{	
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 60);
	

	label = gtk_label_new("label");
	button = gtk_button_new_with_label("Post message to server");
	entry = gtk_entry_new();
	
	gtk_signal_connect(GTK_OBJECT(window), "destory",
		GTK_SIGNAL_FUNC(gtk_main_quit), NULL);
	gtk_signal_connect(GTK_OBJECT(button),"clicked",
		GTK_SIGNAL_FUNC(button_clicked), NULL);
	
	vbox = gtk_vbox_new(FALSE, 10);
	gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(vbox), entry, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, FALSE, 5);
 	

	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
