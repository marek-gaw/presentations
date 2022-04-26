```
SecurityEvent
| where TimeGenerated >= ago(30d)
| where EventID == 4625
| project TimeGenerated, Account, Computer, EventID, Activity, IpAddress
| summarize FailedLogons = count() by Computer
| order by FailedLogons
| render piechart
```

```
Perf
| where ObjectName == "Process"
| where CounterName == "% Processor Time"
| where CounterValue > 0
| extend CPUTime = strcat(tostring(round(CounterValue, 1)), "%")
| project TimeGenerated, Computer, InstanceName, CounterValue, CPUTime
| summarize arg_max(TimeGenerated, *) by Computer
| order by CounterValue desc
```