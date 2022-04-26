---
marp: true
---

<!-- 

Nie chcę recenzować dokumentacji
Jest mnóstwo filmów gdzie kompetentni ludzie opowiajdają o ADX
Ja chcę opowiedzieć o sytuacjach z życia, gdzie można na tą usługę trafić i jak ją wykorzystać

Set and settings

- prezentacja 45 min, 10 min na pytania
- kontakt ze mną: linkedin

Setka:
An Azure Data Explorer cluster is a pair of engine and data management clusters which uses several Azure resources such as Azure Linux VM’s and Storage. The applicable VMs, Azure Storage, Azure Networking and Azure Load balancer costs are billed directly to the customer subscription.
Azure Data Explorer clusters are billed on a per minute basis. Azure Data Explorer charges you for each VM in the cluster as well as Azure Data Explorer markup for some components of a cluster. Azure Data Explorer markup is proportional to the number of the VM vCores running in the engine cluster.
-->


### Fun fact

ADX is used by MS internally:
- Windows
- Skype
- Linkedin
- Visual Studio
- Office
- Xbox
- _Azure_
- PaaS offerings based on ADX

---

## Who am I?

- any-stack developer
- current area: IoT
- Technology Evangelist @ ABB
- [C/Embedded/Hardware User Group](https://www.facebook.com/groups/239943109748231/about/) organizer

---

### Pros and cons
<!-- page_number: true -->
<!-- _class: split -->

<div class=ldiv>

#### Pros
- telemetry
- simple data analysis

</div>
<div class=rdiv>

#### cons

- debugging

</div>

---

## When (not) to use ADX?

---

![bg fit](https://docs.microsoft.com/en-us/azure/data-explorer/media/data-explorer-overview/decision-tree.png)

---

## Further topics

- [Security](https://docs.microsoft.com/en-us/azure/data-explorer/security)
- [Advanced KQL](https://docs.microsoft.com/en-us/azure/data-explorer/kusto/query/)

---

## Extra

ADX vs Databricks

[Stack Overflow: Azure Data Explorer (ADX) vs Polybase vs Databricks](https://stackoverflow.com/questions/62048884/azure-data-explorer-adx-vs-polybase-vs-databricks)

> 
ADX is dramatically faster for interactive queries over large data sets. If you are using batch processing go for spark. If you want to query fresh and large data sets really quickly, ADX is way faster and easier to use even for non-programmers. – 
Uri Barash
Jun 2 2020 at 19:46


---

### What is time series data?

Time series data

> Time-series data is a sequence of data points collected over time intervals, giving us the ability to track changes over time. Time-series data can track changes over milliseconds, days, or even years.

- need for history of changes instead of last known state

---

### Time series analysis in ADX

<!--
[What the heck is time-series data (and why do I need a time-series database)? ](https://blog.timescale.com/blog/what-the-heck-is-time-series-data-and-why-do-i-need-a-time-series-database-dcf3b1b18563/)
-->

```sql
analiza danych IoT na klastrze Help
```

---

## Why to use ADX?

- explore the data: you know what you are look for
- explore the data: questions are not known

<!-- 
- wiadomo czego się szuka, np rodzaju awarii

- nie wiadomo czego się szuka, biznes ma dane ale nie wie co z nimi zrobić
-->

---

## Why?

- time series data on Azure
- strange query language in Azure Monitor

---

## Azure Sentinel

przykład z Sentinela
<!--
https://techcommunity.microsoft.com/t5/microsoft-sentinel-blog/get-hands-on-kql-practice-with-this-microsoft-sentinel-workbook/ba-p/3055600
-->

[](https://github.com/Azure/Azure-Sentinel/blob/master/Workbooks/IntrotoKQL.json)

---

## Links

### LinkedIn

- Henning Rauch
- Tzvia Gitlin Troyna
- Rod Trent
- Uri Barasch