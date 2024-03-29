
# urls.py

from django.contrib import admin
from django.conf import settings
from django.urls import path, re_path
from django.views.static import serve

urlpatterns = [
    path('admin/', admin.site.urls),
]

if settings.DEBUG:
    urlpatterns += [
        re_path("^media\/(?P<path>.*)$", serve, {
            "document_root": settings.MEDIA_ROOT,
            "show_indexes": True
        })
    ]

# settings.py
MEDIA_ROOT = os.path.join(BASE_DIR, "media")
