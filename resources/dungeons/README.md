# README

The descriptions below assume the following directory structure:

```
dungeons
|
+-- dungeon-01
|  |
|  +-- unprocessed
|  +-- remapped
|  \── upscaled
|
+-- endesga-32-1x.png
```

## remap_batch.sh

This script allows you to batch remap all images of a specified directory.

To remap all images of directory `dungeon-01/unprocessed`, using `endesga-32-1x.png` and output directory `dungeon-01/remapped` you can use the following command:

```bash
./remap_batch.sh dungeon-01/unprocessed endesga-32-1x.png dungeon-01/remapped
```

## hqx_batch.sh

This script allows you to batch upscale all images of a specified directory.

To upscale all images of directory `dungeon-01/remapped` by a factor of `2` and output them to `dungeon-01/upscaled` you can use the following command:

```bash
./hqx_batch.sh dungeon-01/remapped 2 dungeon-01/upscaled
```
