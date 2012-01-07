#mood fly

## Overview

Displayig the mood of a topic on Twitter using green for positive, blue for neutral and red for negative sentiments.

## Details

Sentiments are fetched from [tweet sentiment's api](http://data.tweetsentiments.com:8080/).

The Wifly shield is controlled with a  [modified wifly library](https://github.com/timr/WiFly-Shield/commit/1f4647c3f1c08c4a15a2d06c879543bc473e4e87) which is Arduino 1.0 compatible and uses proper Stream instead of Print subclassing.