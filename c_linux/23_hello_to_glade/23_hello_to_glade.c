/*
 ============================================================================
 Name        : 23_hello_to_glade.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include <gtk-2.0/gtk/gtk.h>
#include <glib-2.0/glib.h>
#include <libglade-2.0/glade/glade.h>		// 包含libglade函数库
int main(int argc, char *argv[]) {

	gtk_init(&argc, &argv);					// 初始化GTK+库
	GladeXML *ui;							// 声明GladeXML类型变量
	ui = glade_xml_new("ui.glade", NULL, NULL);// 创建GladeXML对象
	GtkWidget *window;						// 声明GtkWidget类型变量
	window = glade_xml_get_widget(ui, "MainWindow");// 从GladeXml对象获得GtkWidget界面构件
	GtkWidget *label;
	label = glade_xml_get_widget(ui, "label");
	gtk_label_set_label(GTK_LABEL(label), "Hello Glade C");// 修改界面构件属性
	gtk_widget_show_all(window);			// 显示window内的所有构件
	glade_xml_signal_autoconnect(ui);		// 连接GladeXML对象所有已定义信号
	gtk_main();								// 开始GTK+主循环
	return EXIT_SUCCESS;
}
