from django.db import models

# Create your models here.
class message(models.Model):
    temperature=models.IntegerField(default=0)
    humi=models.IntegerField(default=0)
    fire=models.BooleanField(default=False)
    gas=models.BooleanField(default=False)
    time=models.TimeField("date published")


class danger_msg(models.Model):
    if_pos_danger=models.BooleanField(default=False)
    if_obj_danger=models.BooleanField(default=False)