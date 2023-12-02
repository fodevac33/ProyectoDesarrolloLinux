<script lang="ts">
    import { type TableSource, Table } from "@skeletonlabs/skeleton";
    import { tableMapperValues } from "@skeletonlabs/skeleton";

    const tableData = [
        {position: 1, dato: "Temp Ambiente", valor: 31.3 },
        {position: 1, dato: "Temp Motor", valor: 51.8 },
        {position: 1, dato: "Latitud", valor: 5.3231},
        {position: 1, dato: "Longitud", valor: -71.3123 },
    ]


    const tableSimple: TableSource = {
        // A list of heading labels.
        head: ['Dato', 'Valor'],
        // The data visibly shown in your table body UI.
        body: tableMapperValues(tableData, ['dato', 'valor']),
    };
                    
</script>

<div class="m-4 shadow-lg">
    <Table source={tableSimple} />
</div>
