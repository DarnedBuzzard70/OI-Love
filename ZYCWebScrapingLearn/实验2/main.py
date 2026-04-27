import requests
from bs4 import BeautifulSoup
import os
import pandas as pd
import time
import random

headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36'
}

url_base = 'https://www.iqiyi.com/ranks1/1/'
url = 'https://www.iqiyi.com/ranks1/1/0'

shuzhi_dict = {
    "热播榜": 0,
    "飙升榜": -1,
    "免费榜": -18,
    "必看榜": -6,
    "上新榜": -5,
    "票房榜": -22,
    "高分榜": -4,
    "N刷榜": -21,
    "云影院票房榜": -16,
    "恐怖榜": 7128547076428333,
    "科幻榜": 2771984357569433,
    "悬疑榜": 5836257895783433,
    "动作榜": 7086834452347833,
    "战争榜": 7086834452347833,
    "喜剧榜": 3842875764248933
}

def main():
    try:
        time.sleep(random.uniform(0.5, 2))
        with open("index.md", "w", encoding="utf-8") as f:
            f.write("")
        for key, value in shuzhi_dict.items():
            zurl = url_base + str(value)
            response = requests.get(zurl, headers=headers, timeout=10)
            response.encoding = 'utf-8'
            response.raise_for_status()
            soup = BeautifulSoup(response.text, 'lxml')

            biaoti  = soup.find_all("div", class_="rvi__tit1")
            jianjie = soup.find_all("p", class_="rvi__des2")
            tupian  = soup.find_all("picture", class_="rvi__img rvi__img--v260")
            lianjie = soup.find_all("a", class_="rvi__box rvi__box3 rvi__box--hover")

            titles = []
            for div in biaoti:
                title = div.get("title")
                if title:
                    titles.append(title)
                    # print(title)

            descriptions = []
            for p in jianjie:
                description = p.get("title")
                if description:
                    descriptions.append(description)
                    # print(description)

            images = []
            for picture in tupian:
                img_link = "https:" + picture.get("id")
                if img_link:
                    images.append(img_link)
                    # print(img_link)

            links = []
            for lk in lianjie:
                slk = "https:" + lk.get("href")
                if slk:
                    links.append(slk)
                    # print(slk)

            with open("index.md", "a", encoding="utf-8") as f:
                f.write(f"# {key}\n\n")
                for title, description, image, link in zip(titles, descriptions, images, links):
                    f.write(f"## {title}\n")
                    f.write(f"### 简介: \n{description}\n\n")
                    f.write(f"[![]({image})]({link})\n")
                    f.write("\n")


            if not os.path.exists(key):
                os.makedirs(key)

            file_path = os.path.join(key, "result.txt")

            with open(file_path, "w", encoding="utf-8") as f:
                for title, description, image, link in zip(titles, descriptions, images, links):
                    f.write(f"标题: {title}\n")
                    f.write(f"简介: {description}\n")
                    f.write(f"图片链接: {image}\n")
                    f.write(f"播放链接: {link}\n")
                    f.write("\n")

            if not os.path.exists(key + "/pictures"):
                os.makedirs(key + "/pictures")

            piccnt = 0
            for picture in images:
                piccnt += 1
                if piccnt > 25:
                    break
                pic_path = os.path.join(key + "/pictures", str(piccnt) + ".jpg")
                with open(pic_path, "wb") as f:
                    f.write(requests.get(picture).content)

    except requests.exceptions.RequestException as e:
        print(f"请求异常：{e}")
    except Exception as e:
        print(f"执行异常：{e}")


if __name__ == '__main__':
    main()