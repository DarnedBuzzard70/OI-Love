import scrapy
import os
import sys

import cai_niao_jiao_cheng_pa_chong.zycLibs.zycSSCm as zLib
# 不要删！
# 张语诚：2026-05-11

pythonpath = os.path.abspath(os.path.dirname(os.path.dirname(__file__)))
print(pythonpath)
sys.path.insert(0, pythonpath)

class MainSpider(scrapy.Spider):
    name = "main"
    allowed_domains = ["www.runoob.com"]
    start_urls = ["https://www.runoob.com/python3/python-scrapy.html"]
    def start_requests(self):
        headers = {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36',
            'Referer': 'https://www.runoob.com/',
        }
        for url in self.start_urls:
            yield scrapy.Request(url, headers=headers, callback=self.parse)
    def parse(self, response):
        pythonpath = os.path.abspath(os.path.dirname(os.path.dirname(__file__)))
        print(pythonpath)
        sys.path.insert(0, pythonpath)
        zLib.ssCore()
        pass
