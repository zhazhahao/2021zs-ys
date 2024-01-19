from django.urls import path

from . import views

urlpatterns = [
    path("", views.index, name="index"),
    path("get/",views.get,name="getapi"),
    path("post/",views.post,name="postapi"),
    path("get/pos_obj/", views.get_danger),
    path("post/pos_obj/", views.post_danger),
    path("if_pos_danger/",views.get_pos),
    path("if_obj_danger/",views.get_obj),
]