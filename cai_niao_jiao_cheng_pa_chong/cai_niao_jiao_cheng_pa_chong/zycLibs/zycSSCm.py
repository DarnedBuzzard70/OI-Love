import requests
from bs4 import BeautifulSoup
import json
import time
from multiprocessing import Pool, cpu_count
import os

headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36'
}

def get_chapter_links(url):
    print("正在获取章节列表...")
    response = requests.get(url, headers=headers)
    response.encoding = 'utf-8'
    soup = BeautifulSoup(response.text, 'html.parser')
    
    links_found = []
    tutorial_list = soup.find('div', class_='sidebar-box gallery-list')
    
    if tutorial_list:
        for a_tag in tutorial_list.find_all('a', href=True):
            href = a_tag['href']
            if href.startswith('/python3/') or href.startswith('python3-'):
                if href.startswith('/'):
                    full_url = 'https://www.runoob.com' + href
                elif href.startswith('python3-'):
                    full_url = 'https://www.runoob.com/python3/' + href
                else:
                    full_url = href
                if 'tutorial' not in full_url.lower() and full_url not in links_found:
                    links_found.append(full_url)
    
    print(f"找到 {len(links_found)} 个章节链接")
    return links_found

def get_chapter_content(url):
    try:
        response = requests.get(url, headers=headers)
        response.encoding = 'utf-8'
        soup = BeautifulSoup(response.text, 'html.parser')
        
        title = soup.find('h1').get_text(strip=True) if soup.find('h1') else '未知标题'
        
        article_intro = soup.find('div', class_='article-intro')
        content = ''
        if article_intro:
            content = article_intro.get_text(strip=True)
        
        result = {
            'title': title,
            'url': url,
            'content': content[:300] if len(content) > 300 else content
        }
        # print(f"成功爬取: {title}")
        return result
    except Exception as e:
        print(f"获取章节内容失败 {url}: {e}")
        return None

def ssCore():
    base_url = 'https://www.runoob.com/python3/python3-tutorial.html'
    links = get_chapter_links(base_url)
    if not links:
        print("没有找到任何章节链接")
        return
    start_time = time.time()
    process_num = cpu_count()
    print(f"\n启动 {process_num} 个进程并发爬取")
    with Pool(processes=process_num) as pool:
        all_content = pool.map(get_chapter_content, links)
    all_content = [item for item in all_content if item is not None]
    print(f"成功爬取 {len(all_content)} 个章节内容")
    print(f"\n开始保存数据")
    with open('python3_tutorial.json', 'w', encoding='utf-8') as f:
        json.dump(all_content, f, ensure_ascii=False, indent=2)
    end_time = time.time()
    print(f"\n爬取完成")
    print(f"共获取 {len(all_content)} 个章节内容")
    print(f"耗时: {end_time - start_time:.2f} 秒")
    print("数据已保存到 python3_tutorial.json")

if __name__ == '__main__':
    ssCore()