# Generated by Django 4.1.7 on 2023-09-21 01:59

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('heandelmessage', '0002_rename_fire_message_gas_message_humi_message_sharp'),
    ]

    operations = [
        migrations.AddField(
            model_name='message',
            name='danger_pos',
            field=models.BooleanField(default=False),
        ),
    ]
