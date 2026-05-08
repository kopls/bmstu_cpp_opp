# commands

Команды переписаны в стиле паттерна Command: команда хранит receiver-object, указатель на метод receiver'а и данные для вызова метода.

Например, `MoveModel` хранит:

- `std::shared_ptr<TransformManager>` как receiver;
- `void (TransformManager::*)(const std::shared_ptr<Object>&, double, double, double)` как action;
- `id`, `dx`, `dy`, `dz` как данные метода.

При `execute()` команда берёт объект из текущей сцены по `id` и вызывает сохранённый метод у receiver'а.

Важно: для этого варианта методы `TransformManager::moveObject/scaleObject/rotateObject/transformObject` должны быть обычными нестатическими методами, потому что команда хранит именно pointer-to-member.
