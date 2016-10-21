<div class="col-sm-2 left-nav">
    <ul class="left-nav-l">
        @if(isset($menu_error))
            <h3>{{$menu_error}}</h3>
        @else
        	@if(isset($menu_list))
                @foreach($menu_list as $menu_item)
                    <li>
                        <a data-toggle="collapse" href="javascript:void(0)" data-target="#{{$menu_item['name']}}"><i class="{{$menu_item["icon"]}}"></i> <span>{{$menu_item["name"]}}</span></a>
                        <ul id="{{$menu_item['name']}}" class="collapse ul-child">
                            @if($menu_item['child'])
                                @foreach($menu_item['child'] as $menu_item_child)
                                    <li><a href="{{url($menu_item_child['url'])}}" target="appiframe-0"><i class="icon-double-angle-right"></i> {{$menu_item_child["name"]}}</a></li>
                                @endforeach
                            @endif
                        </ul>
                    </li>
                @endforeach
            @endif
        @endif
    </ul>
</div>