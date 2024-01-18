from django.shortcuts import render
from django.http import JsonResponse
import json
from heandelmessage.models import message,danger_msg
from django.utils import timezone
# Create your views here.
from django.http import HttpResponse

def index(request):
    return HttpResponse("hello,my!")

def post(request):
    date=request.body.decode("utf-8")
    json_data=json.loads(date)
    tem=json_data.get("temperature")
    humi=json_data.get("humi")
    fire=json_data.get("fire")
    gas=json_data.get("gas")
    print("-----")
    print(tem)
    print(humi)
    print(gas)
    print("----")
    p=message(temperature=tem,humi=humi,fire=fire,gas=gas,time=timezone.now())
    p.save()
    return HttpResponse("ok")
def post_danger(request):
    date=request.body.decode("utf-8")
    json_data=json.loads(date)
    if_pos_danger=json_data.get("if_pos_danger")
    if_obj_danger = json_data.get("if_obj_danger")
    p=danger_msg(if_pos_danger=if_pos_danger,if_obj_danger=if_obj_danger)
    p.save()
    return HttpResponse("ok")
def get(request):
    data=message.objects.last()
    return JsonResponse({"temper":data.temperature,"humi":data.humi,"fire":data.fire,"gas":data.gas})

def get_danger(request):
    data = danger_msg.objects.last()
    return JsonResponse({"if_pos_danger": data.if_pos_danger, "if_obj_danger": data.if_obj_danger})
def get_pos(request):
    file_path = "pos.txt"  # 替换为你的文件路径
    file = open(file_path, "r")
    first_line = file.readline()
    file.close()
    return JsonResponse({"pos_danger":(int)(first_line)})

def get_obj(request):
    file_path = "obj.txt"  # 替换为你的文件路径
    file = open(file_path, "r")
    first_line = file.readline()
    file.close()
    return JsonResponse({"obj_danger":(int)(first_line)})