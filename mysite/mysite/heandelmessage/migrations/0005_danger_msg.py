# Generated by Django 4.2.2 on 2023-10-12 12:42

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ("heandelmessage", "0004_rename_danger_pos_message_fire_remove_message_sharp"),
    ]

    operations = [
        migrations.CreateModel(
            name="danger_msg",
            fields=[
                (
                    "id",
                    models.BigAutoField(
                        auto_created=True,
                        primary_key=True,
                        serialize=False,
                        verbose_name="ID",
                    ),
                ),
                ("if_pos_danger", models.BooleanField(default=False)),
                ("if_obj_danger", models.BooleanField(default=False)),
            ],
        ),
    ]
